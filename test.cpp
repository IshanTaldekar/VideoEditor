
#ifndef ONCE_ONLY_ONCE
#define ONCE_ONLY_ONCE
#include "Dependencies.h"

#include<stdio.h>
#include<string>
//#include<io.h>
#include<unistd.h>
#include<vector>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
using namespace std;
extern "C"
{
#include"libavformat/avformat.h"
#include"libavcodec/avcodec.h"
#include"libavutil/time.h"
#include"libavutil/log.h"
}


/* Understand how this looping works.
 * Adapt it in your code.
 * Loop the background to the appropriate length. audio - intro.
 * Then figure out how to concat different ones.
 */


int test_this()
{
    //av_register_all();

    avformat_network_init();

    string path_v = "output_file.mp4";
    string url_v = "new_output_file.mp4";

    AVFormatContext *pFormatCtxV = nullptr;
    AVFormatContext *pFormatCtxV_O = nullptr;

    int64_t cur_pts_v = 0, cur_pts_a = 0;

    int re = avformat_open_input(&pFormatCtxV, path_v.c_str(), nullptr, nullptr);
    if (re != 0)
    {
        // // printf("");
    }


    re = avformat_find_stream_info(pFormatCtxV, nullptr);
    if (re < 0)
    {
        // // printf("");
    }


    //
    // printf("******************\n");
    av_dump_format(pFormatCtxV, 0, url_v.c_str(), 0);
    // printf("******************\n");
    //

    int iIndex_v = -1, iIndex_a = -1;

    for (int i = 0; i < pFormatCtxV->nb_streams; i++)
    {
        if (pFormatCtxV->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            iIndex_v = i;
            break;
        }
    }


    re = avformat_alloc_output_context2(&pFormatCtxV_O, nullptr, nullptr, url_v.c_str());
    if (re < 0)
    {
        // printf("");
    }

    AVCodecContext *pCodecCtxV = avcodec_alloc_context3(NULL);
    avcodec_parameters_to_context(pCodecCtxV, pFormatCtxV->streams[iIndex_v]->codecpar);

    //AVFormatContext???????AVStream????.
    AVStream *pV = avformat_new_stream(pFormatCtxV_O, pCodecCtxV->codec);

    //AVstream????????codecpar???.
    re = avcodec_parameters_copy(pV->codecpar, pFormatCtxV->streams[iIndex_v]->codecpar);
    if (re < 0)
    {
        // printf("");
    }

    AVCodecContext *pCodecCtxA = avcodec_alloc_context3(NULL);


    //
    // printf("****************\n");

    av_dump_format(pFormatCtxV_O, 0, url_v.c_str(), 1);
    // printf("****************\n");
    //pFormatCtxA_O->pb->direct = 1;


    re = avio_open(&pFormatCtxV_O->pb, url_v.c_str(), AVIO_FLAG_WRITE);

    if (re < 0)
    {
        // printf("");
    }

    //
    re = avformat_write_header(pFormatCtxV_O, nullptr);



    AVPacket pkt;
    int iFrame_index = 0;
    int iAFrame_index = 0;
    int64_t i64Start = av_gettime();
    bool double_it {true};

    while (true)
    {
        re = av_read_frame(pFormatCtxV, &pkt);
        // printf("ret =%d, pos:%ld\n",re, pkt.pos);
        if (re < 0  )
        {
            if(re==AVERROR_EOF && double_it) {

                double_it = false;
                avio_seek(pFormatCtxV->pb, -1, SEEK_SET);
                avformat_seek_file(pFormatCtxV, 0, 0, 0, pFormatCtxV->streams[0]->duration, 0);
                //  int ret = av_seek_frame(pFormatCtxV, -1, pFormatCtxV->start_time/*+(180.0) * AV_TIME_BASE*/, AVSEEK_FLAG_BACKWARD);
                // printf("avformat_seek_file ret =%d\n",ret);
                continue;
            }else {
                // printf("av_read_frame error:%d\n",re);
                break;
            }
        }

        if (pkt.stream_index == iIndex_v)
        {
            AVRational time_base = pFormatCtxV->streams[iIndex_v]->time_base;
            // printf("time_base :%d\n",time_base);
            AVRational r_famerate = pFormatCtxV->streams[iIndex_v]->r_frame_rate;
            AVRational time_base_q = {1,AV_TIME_BASE};

            int64_t calc_duation = double(AV_TIME_BASE) / av_q2d(r_famerate);
            // printf("calc_duation:%d\n",calc_duation);

            pkt.pts = av_rescale_q(iFrame_index *calc_duation, time_base_q, time_base);
            // printf("tpkt.pts :%d\n",pkt.pts);
            pkt.dts = pkt.pts;
            pkt.duration = av_rescale_q(calc_duation, time_base_q, time_base);

            cur_pts_v = pkt.pts;

            iFrame_index++;

            {//???????

                AVRational time_base = pFormatCtxV->streams[iIndex_v]->time_base;
                AVRational time_base_q = {1,AV_TIME_BASE};
                int64_t pts_time = av_rescale_q(pkt.pts, time_base, time_base_q);
                int64_t now_time = av_gettime() - i64Start;
                if (pts_time > now_time)
                {
                    av_usleep(pts_time - now_time);
                }
            }
            pkt.pts = av_rescale_q_rnd(pkt.pts, time_base, pFormatCtxV_O->streams[0]->time_base, (enum AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
            // printf("pkt.pts :%d\n",pkt.pts);
            pkt.dts = av_rescale_q_rnd(pkt.dts, time_base, pFormatCtxV_O->streams[0]->time_base, (enum AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
            pkt.duration = av_rescale_q(pkt.duration,time_base, pFormatCtxV_O->streams[0]->time_base);

            //av_interleaved_write_frame(pFormatCtxV_O, &pkt);
            av_write_frame(pFormatCtxV_O, &pkt);
        }
        av_packet_unref(&pkt);

    }

    av_write_trailer(pFormatCtxV_O);

    avformat_close_input(&pFormatCtxV);

    avformat_free_context(pFormatCtxV_O);
    // printf("end\n");
    getchar();

    return 0;

}

#endif
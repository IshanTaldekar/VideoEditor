#include "MediaProcessor.h"

/*
 * TODO: Rewrite functions.
 *
 * !!! THIS CODE IS INCOMPLETE AND INCORRECT !!!
 *
 */


/**
 * Loop background video to match the duration of the audio file provided.
 *
 * @return true if operation was successful.
 */
bool MediaProcessor::transcode_and_extend_background_video() {

    AVCodecContext *codec_context{avcodec_alloc_context3(background_file_components.codec)};

    if (!codec_context) {

        return false;
    }

    if (avcodec_parameters_to_context(codec_context, background_file_components.codec_parameters) < 0) {

        return false;
    }

    if (avcodec_open2(codec_context, background_file_components.codec, nullptr) < 0) {

        return false;
    }

    AVFrame *media_frame{av_frame_alloc()};

    if (!media_frame) {

        return false;
    }

    AVPacket *media_packet{av_packet_alloc()};

    if (!media_packet) {

        return false;
    }

    int streams_count{static_cast<int>(background_file_components.format_context->nb_streams)};
    int *streams_list{static_cast<int *>(av_mallocz_array(streams_count, sizeof(*streams_list)))};

    if (!streams_list) {

        log_message("ERROR: stream list allocation failed.");
        return false;

    }

    // get video stream information, index.
    // find new encoder by name.
    // use the encoder name to allocate the output format context.
    // set options: preset fast.
    // set other information.
    // open codec.
    // allocate memory for output packet.
    // transcode video and then encode it.
    // write it (encode video is necessary).
    while (av_read_frame(background_file_components.format_context, media_packet) >= 0) {

        if (media_packet->stream_index == background_file_components.stream_index) {

            /*
            AVStream *input_stream, *new_output_stream;

            input_stream = background_file_components.format_context->streams[media_packet->stream_index];
            media_packet->stream_index = streams_list[media_packet->stream_index];
            new_output_stream = output_file_components.format_context->streams[media_packet->stream_index];

            /* Copy packet: *\/
            media_packet->pts = av_rescale_q_rnd(media_packet->pts, input_stream->time_base, new_output_stream->time_base,
                                                 static_cast<AVRounding>(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));

            media_packet->dts = av_rescale_q_rnd(media_packet->dts, input_stream->time_base, new_output_stream->time_base,
                                                 static_cast<AVRounding>(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));

            media_packet->pos = -1;

            if (av_interleaved_write_frame(output_file_components.format_context, media_packet) < 0) {

                log_message("ERROR: packet muxing failed.");
                return false;

            }

            av_packet_unref(media_packet);
             */

            if (!transcode_video(background_file_components, media_packet, media_frame)) return false;
            av_packet_unref(media_packet);

        }
    }

    if (encode_video(background_file_components,nullptr)) return false;

    return true;

}


/**
 *
 */
bool MediaProcessor::set_output_file_components() {

    log_message("Setting output file format.");

    output_file_components.name = "output_file"; // TODO: set with GUI eventually.
    output_file_components.name += state.output_file_container;

    avformat_alloc_output_context2(&output_file_components.format_context, nullptr, nullptr, output_file_components.name.c_str());

    if (output_file_components.format_context == nullptr) {

        log_message("ERROR: output format context creation failed.");
        return false;

    }

    if ((output_file_components.stream = avformat_new_stream(output_file_components.format_context, nullptr)) == nullptr) {

        log_message("ERROR: output video stream allocation failed.");
        return false;

    }

    AVRational background_video_frame_rate {av_guess_frame_rate(background_file_components.format_context, background_file_components.stream, nullptr)};


    if ((output_file_components.codec = avcodec_find_encoder_by_name(state.output_media_codec.c_str())) == nullptr) {

        log_message("ERROR: codec not found.");
        return false;

    }

    if ((output_file_components.codec_context = avcodec_alloc_context3(output_file_components.codec)) == nullptr) {

        log_message("ERROR: could not allocate codec context.");
        return false;

    }

    av_opt_set(output_file_components.codec_context->priv_data, "preset", "ultrafast", 0);

    if (output_file_components.codec_context->priv_data && state.output_codec_priv_value.c_str()) {

        av_opt_set(output_file_components.codec_context->priv_data, state.output_codec_priv_key.c_str(),
                   state.output_codec_priv_value.c_str(), 0);

    }

    output_file_components.codec_context->height = background_file_components.codec_context->height;
    output_file_components.codec_context->width = background_file_components.codec_context->width;
    output_file_components.codec_context->sample_aspect_ratio = background_file_components.codec_context->sample_aspect_ratio;

    if (output_file_components.codec->pix_fmts) output_file_components.codec_context->pix_fmt = output_file_components.codec->pix_fmts[0];
    else output_file_components.codec_context->pix_fmt = background_file_components.codec_context->pix_fmt;

    output_file_components.codec_context->color_primaries = AVCOL_PRI_BT709;

    output_file_components.codec_context->bit_rate = state.bitrate;
    output_file_components.codec_context->rc_buffer_size = state.rc_buffer_size;
    output_file_components.codec_context->rc_max_rate = state.rc_max_rate;
    output_file_components.codec_context->rc_min_rate = state.rc_min_rate;


    output_file_components.codec_context->time_base = av_inv_q(background_video_frame_rate);
    output_file_components.stream->time_base = output_file_components.codec_context->time_base;

    if (avcodec_open2(output_file_components.codec_context, output_file_components.codec, nullptr) < 0) {

        log_message("ERROR: failed to open codec.");
        return false;

    }

    avcodec_parameters_from_context(output_file_components.stream->codecpar, output_file_components.codec_context);

    if (output_file_components.format_context->oformat->flags & AVFMT_GLOBALHEADER) {

        output_file_components.format_context->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;

    }

    if (!(output_file_components.format_context->oformat->flags & AVFMT_NOFILE)
        && avio_open(&output_file_components.format_context->pb, output_file_components.name.c_str(), AVIO_FLAG_WRITE)) {

        log_message("ERROR: could not open output file.");
        return false;

    }

    AVDictionary* packet_muxer_options {nullptr};

    if (!state.output_muxer_opt_key.empty() && !state.output_muxer_opt_value.empty()) {

        av_dict_set(&packet_muxer_options, state.output_muxer_opt_key.c_str(), state.output_muxer_opt_value.c_str(), 0);

    }

    if (avformat_write_header(output_file_components.format_context, &packet_muxer_options) < 0) {

        log_message("ERROR: output file failed to open.");
        return false;

    }

    log_message("DONE: output file setup for encoding.");
    return true;

}


/**
 *
 * @param decode_file_components
 * @param encode_file_components
 * @param media_packet
 * @param media_frame
 */
bool MediaProcessor::transcode_video(FileComponents decode_file_components, AVPacket *media_packet, AVFrame *media_frame) {

    log_message("Transcoding streams from file: " + decode_file_components.name);

    int response {0};

    if ((response = avcodec_send_packet(decode_file_components.codec_context, media_packet)) < 0) {

        log_message("ERROR: send to decoder failed.");
        return false;

    }

    while (response >= 0) {

        response = avcodec_receive_frame(decode_file_components.codec_context, media_frame);

        if (response == AVERROR(EAGAIN) || response == AVERROR_EOF) break;
        else if (response < 0) {

            log_message("ERROR: recieve from decoder failed.");
            return false;

        }

        if (response >= 0 && !(encode_video(decode_file_components, media_frame))) return false;

        av_frame_unref(media_frame);

    }

    log_message("DONE: video transcoded successfully.");
    return true;

}


/**
 *
 * @param decode_file_components
 * @param encode_file_components
 * @param input_frame
 */
bool MediaProcessor::encode_video(FileComponents decode_file_components, AVFrame *media_frame) {

    log_message("Encoding data from file: " + decode_file_components.name);
    if(media_frame) media_frame->pict_type = AV_PICTURE_TYPE_NONE;

    AVPacket *output_packet {av_packet_alloc()};

    if (!output_packet) {

        log_message("ERROR: failed to allocate output packet.");
        return false;

    }

    int response {avcodec_send_frame(output_file_components.codec_context, media_frame)};

    while (response >= 0) {

        response = avcodec_receive_packet(output_file_components.codec_context, output_packet);

        if (response == AVERROR(EAGAIN) || response == AVERROR_EOF) break;
        else if (response < 0) {

            log_message("ERROR: receive packet from encoder failed.");
            return false;

        }

        output_packet->stream_index = decode_file_components.stream_index;
        output_packet->duration = (output_file_components.stream->time_base.den / output_file_components.stream->time_base.num /
                                   decode_file_components.stream->avg_frame_rate.num * decode_file_components.stream->avg_frame_rate.den);

        av_packet_rescale_ts(output_packet, decode_file_components.stream->time_base, output_file_components.stream->time_base);

        if ((response = av_interleaved_write_frame(output_file_components.format_context, output_packet)) != 0) {

            log_message("ERROR: failed to receive packet from decoder.");
            return false;

        }

    }

    av_packet_unref(output_packet);
    av_packet_free(&output_packet);
    return true;

}


/**
 *
 * @return
 */
bool MediaProcessor::execute() {

    set_output_file_components();
    transcode_and_extend_background_video();
    write_output_video();

    return true;

}


/**
 *
 * @return
 */
bool MediaProcessor::write_output_video() {

    av_write_trailer(output_file_components.format_context);
    return true;

}
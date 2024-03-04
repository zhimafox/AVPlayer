#ifndef FXAUDIOOUTPUT_H
#define FXAUDIOOUTPUT_H
namespace fox
{
    namespace player
    {
        typedef struct FxAudioParams {
            int freq;//采样率
            int channels;
            long channel_layout;
            // enum AVSampleFormat fmt;
            int frameSize;
        }FxAudioParams;

        class FxAudioOutput
        {
        public:
            FxAudioOutput();
            ~FxAudioOutput();
            int init();
            int deInit();
        private:
            FxAudioParams pSrcAudioparams; //解码后的参数
            FxAudioParams pDstAudioparams; //SDL实际输出格式
        };
    }// namespace player
}// namespace fox
#endif // FXAUDIOOUTPUT_H

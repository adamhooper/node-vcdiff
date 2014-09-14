#include "vcd_encoder.h"

#include "third-party/open-vcdiff/src/google/vcencoder.h"

VcdEncoder::VcdEncoder(
    v8::Local<v8::Object> hashed_dictionary,
    std::unique_ptr<open_vcdiff::VCDiffStreamingEncoder> encoder)
    : encoder_(std::move(encoder)),
      hashed_dictionary_(v8::Persistent<v8::Object>::New(hashed_dictionary)) {
}

VcdEncoder::~VcdEncoder() {
}

VcdCtx::Error VcdEncoder::Start(open_vcdiff::OutputStringInterface* out) {
  if (!encoder_->StartEncodingToInterface(out))
    return VcdCtx::Error::INIT_ERROR;
  return VcdCtx::Error::OK;
}

VcdCtx::Error VcdEncoder::Process(const char* data,
                                  size_t len,
                                  open_vcdiff::OutputStringInterface* out) {
  if (!encoder_->EncodeChunkToInterface(data, len, out))
    return VcdCtx::Error::ENCODE_ERROR;
  return VcdCtx::Error::OK;
}

VcdCtx::Error VcdEncoder::Finish(open_vcdiff::OutputStringInterface* out) {
  encoder_->FinishEncodingToInterface(out);
  return VcdCtx::Error::OK;
}

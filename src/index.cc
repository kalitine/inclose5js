#include <napi.h>
#include <stdio.h>
#include "../lib/inclose5/stdafx.h"
#include "../lib/inclose5/globalsv.h"
#include "../lib/inclose5/inclose.h"
#include "../lib/inclose5/BicsUtils.h"

static void ArrayConsumer(dataset_t &matrix, const uint8_t* array, size_t length, row_t row_size, col_t col_size  ) {

  //Allocating memory
	matrix = new data_t*[row_size];
	for (row_t i = 0; i < row_size; ++i)
		matrix[i] = new data_t[col_size];

  row_t i = 0;
  row_t j = 0;
  for (size_t index = 0; index < length; index++) {
    if (j == col_size) {
      j = 0;
      i++;
    }
    if (i < row_size) {
      matrix[i][j] = array[index] == 1 ? true : false;
      j++;
    }
  }
}

static Napi::Value Run(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 3) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsArrayBuffer() || !info[1].IsNumber() || !info[2].IsNumber()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }


  row_t row_size = info[1].As<Napi::Number>().Int32Value();
  col_t col_size = info[2].As<Napi::Number>().Int32Value();
  Napi::ArrayBuffer buf = info[0].As<Napi::ArrayBuffer>();
  dataset_t matrix;
  ArrayConsumer(matrix, reinterpret_cast<uint8_t*>(buf.Data()),
                buf.ByteLength() / sizeof(uint8_t), row_size, col_size);

	double duration = runInClose(matrix, row_size, col_size, 2, 1);
  Napi::Number durationN = Napi::Number::New(env, duration);

  return durationN;
}

static Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "run"), Napi::Function::New(env, Run));
  return exports;
}

NODE_API_MODULE(inclose5, Init)
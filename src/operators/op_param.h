/* Copyright (c) 2018 PaddlePaddle Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#pragma once

#include <string>
#include <vector>
#include "common/log.h"
#include "common/type_define.h"
#include "common/types.h"
#include "framework/lod_tensor.h"
#include "framework/scope.h"
#include "framework/tensor.h"
#include "framework/tensor_wrapper.h"
#include "framework/variable.h"

#ifdef PADDLE_MOBILE_FPGA_V1
#include "fpga/V1/api.h"
#endif

#ifdef PADDLE_MOBILE_FPGA_V2
#include "fpga/V2/api.h"
#endif

#ifdef PADDLE_MOBILE_CL
#include "framework/cl/cl_image.h"
#endif

namespace paddle_mobile {
namespace operators {

using framework::Attribute;
using framework::AttributeMap;
using framework::LoDTensor;
using framework::Scope;
using framework::Tensor;
using framework::Variable;
using std::string;
using std::vector;

struct DtypeTensorTrait {
  //  typedef framework::TensorWrapper wtype;

  // This is the type we obtained in variable.
  typedef framework::TensorWrapper gtype;
  // This type will be the parent class type
  // or the same type.
  typedef framework::TensorWrapper rtype;
};

/*template <>
struct DtypeTensorTrait {
  //  typedef framework::TensorWrapper wtype;

  // This is the type we obtained in variable.
  typedef framework::TensorWrapper gtype;
  // This type will be the parent class type
  // or the same type.
  typedef framework::LoDTensor rtype;
};

#ifdef PADDLE_MOBILE_CL
template <>
struct DtypeTensorTrait<GPU_CL> {
  // This is the type we obtained in variable.
  typedef framework::TensorWrapper gtype;
  // This type will be the parent class type
  // or the same type.
  typedef framework::CLImage rtype;

  //  typedef framework::TensorWrapper wtype;
};
#endif*/

class OpParam {
 public:
  OpParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
          const AttributeMap &attrs, Scope *scope) {
    scope_pointer_ = scope;
    inputs_ = inputs;
  }

  template <typename T>
  T *CreateNewScale() {
    std::string scale_key = Getkey("Scale", inputs_, 0);
    auto var = scope_pointer_->Var(scale_key + "_new");
    return var->GetMutable<T>();
  }

  template <typename T>
  T *CreateNewBiase() {
    std::string biase_key = Getkey("Bias", inputs_, 0);
    auto var = scope_pointer_->Var(biase_key + "_new");
    return var->GetMutable<T>();
  }

  VariableNameMap inputs_;
  Scope *scope_pointer_ = nullptr;

 protected:
  template <typename T>
  static T *InputH0From(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("H0", inputs, scope);
  }

  template <typename T>
  static T *InputHiddenPrevFrom(const VariableNameMap &inputs,
                                const Scope &scope) {
    return GetVarValue<T>("HiddenPrev", inputs, scope);
  }

  template <typename T>
  static T *InputAlphaFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("Alpha", inputs, scope);
  }

  template <typename T>
  static T *InputFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("Input", inputs, scope);
  }

  template <typename T>
  static T *InputXFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("X", inputs, scope);
  }
  template <typename T>
  static T *InputOutSizeFrom(const VariableNameMap &inputs,
                             const Scope &scope) {
    return GetVarValue<T>("OutSize", inputs, scope);
  }

  template <typename T>
  static T *InputWFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("W", inputs, scope);
  }

  template <typename T>
  static T *InputIdsFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("Ids", inputs, scope);
  }

  template <typename T>
  static T *InputEmissionFrom(const VariableNameMap &inputs,
                              const Scope &scope) {
    return GetVarValue<T>("Emission", inputs, scope);
  }

  template <typename T>
  static T *InputTransitionFrom(const VariableNameMap &inputs,
                                const Scope &scope) {
    return GetVarValue<T>("Transition", inputs, scope);
  }
  template <typename T>
  static T *InputLabelFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("Label", inputs, scope);
  }

  template <typename T>
  static T *InputXFrom1(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue1<T>("addX", inputs, scope);
  }

  template <typename T>
  static T *InputYFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("Y", inputs, scope);
  }

  template <typename T>
  static T *InputYFrom1(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue1<T>("Y", inputs, scope);
  }

  template <typename T>
  static T *InputZFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("Z", inputs, scope);
  }

  template <typename T>
  static T *InputBiasFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("Bias", inputs, scope);
  }
  template <typename T>
  static T *InputWeightFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("Weight", inputs, scope);
  }
  template <typename T>
  static T *InputVarianceFrom(const VariableNameMap &inputs,
                              const Scope &scope) {
    return GetVarValue<T>("Variance", inputs, scope);
  }
  template <typename T>
  static T *InputMeanFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("Mean", inputs, scope);
  }
  template <typename T>
  static T *InputScaleFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("Scale", inputs, scope);
  }
  template <typename T>
  static T *InputImageFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("Image", inputs, scope);
  }
  template <typename T>
  static T *InputPriorBoxFrom(const VariableNameMap &inputs,
                              const Scope &scope) {
    return GetVarValue<T>("PriorBox", inputs, scope);
  }
  template <typename T>
  static T *InputPriorBoxVarFrom(const VariableNameMap &inputs,
                                 const Scope &scope) {
    return GetVarValue<T>("PriorBoxVar", inputs, scope);
  }
  // LoDTensor but now use Tensor
  template <typename T>
  static T *InputTargetBoxFrom(const VariableNameMap &inputs,
                               const Scope &scope) {
    return GetVarValue<T>("TargetBox", inputs, scope);
  }

  template <typename T>
  static T *InputBBoxesFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("BBoxes", inputs, scope);
  }

  template <typename T>
  static T *InputScoresFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("Scores", inputs, scope);
  }

  template <typename T>
  static T *InputShapeFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("Shape", inputs, scope);
  }

  template <typename T>
  static vector<T *> InputMultiFrom(const VariableNameMap &inputs,
                                    const Scope &scope) {
    return GetMultiVarValue<T>("X", inputs, scope);
  }

  static vector<Variable *> InputMultiVarsFrom(const VariableNameMap &inputs,
                                               const Scope &scope) {
    return GetMultiVar("X", inputs, scope);
  }

  template <typename T>
  static T *OutputBatchGateFrom(const VariableNameMap &outputs,
                                const Scope &scope) {
    return GetVarValue<T>("BatchGate", outputs, scope);
  }

  template <typename T>
  static T *OutputGateFrom(const VariableNameMap &outputs, const Scope &scope) {
    return GetVarValue<T>("Gate", outputs, scope);
  }

  template <typename T>
  static T *OutputViterbiPathFrom(const VariableNameMap &outputs,
                                  const Scope &scope) {
    return GetVarValue<T>("ViterbiPath", outputs, scope);
  }
  template <typename T>
  static T *OutputBatchResetHiddenPrevFrom(const VariableNameMap &outputs,
                                           const Scope &scope) {
    return GetVarValue<T>("BatchResetHiddenPrev", outputs, scope);
  }

  template <typename T>
  static T *OutputResetHiddenPrevFrom(const VariableNameMap &outputs,
                                      const Scope &scope) {
    return GetVarValue<T>("ResetHiddenPrev", outputs, scope);
  }

  template <typename T>
  static T *OutputBatchHiddenFrom(const VariableNameMap &outputs,
                                  const Scope &scope) {
    return GetVarValue<T>("BatchHidden", outputs, scope);
  }

  template <typename T>
  static T *OutputHiddenFrom(const VariableNameMap &outputs,
                             const Scope &scope) {
    return GetVarValue<T>("Hidden", outputs, scope);
  }

  template <typename T>
  static T *OutputFrom(const VariableNameMap &outputs, const Scope &scope) {
    return GetVarValue<T>("Output", outputs, scope);
  }

  static Variable *OutVarFrom(const VariableNameMap &outputs,
                              const Scope &scope) {
    return GetVar("Out", outputs, scope);
  }

  template <typename T>
  static T *OutFrom(const VariableNameMap &outputs, const Scope &scope) {
    return GetVarValue<T>("Out", outputs, scope);
  }

  template <typename T>
  static vector<T *> OutMultiFrom(const VariableNameMap &outputs,
                                  const Scope &scope) {
    return GetMultiVarValue<T>("Out", outputs, scope);
  }

  template <typename T>
  static T *OutputYFrom(const VariableNameMap &outputs, const Scope &scope) {
    return GetVarValue<T>("Y", outputs, scope);
  }

  template <typename T>
  static T *OutputXShapeFrom(const VariableNameMap &outputs,
                             const Scope &scope) {
    return GetVarValue<T>("XShape", outputs, scope);
  }

  template <typename T>
  static T *OutputBoxesFrom(const VariableNameMap &outputs,
                            const Scope &scope) {
    return GetVarValue<T>("Boxes", outputs, scope);
  }

  template <typename T>
  static T *OutputBoxFrom(const VariableNameMap &outputs, const Scope &scope) {
    return GetVarValue<T>("OutputBox", outputs, scope);
  }

  template <typename T>
  static T *OutputNormFrom(const VariableNameMap &outputs, const Scope &scope) {
    return GetVarValue<T>("Norm", outputs, scope);
  }

  template <typename T>
  static T *OutputVariancesFrom(const VariableNameMap &outputs,
                                const Scope &scope) {
    return GetVarValue<T>("Variances", outputs, scope);
  }

  template <typename T>
  static T *MidOutFrom(const VariableNameMap &outputs, const Scope &scope) {
    return GetVarValue<T>("MidOut", outputs, scope);
  }

  template <typename T>
  static T *FilterFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("Filter", inputs, scope);
  }

  template <typename T>
  static const T GetAttr(const string &key, const AttributeMap &map) {
    return ((Attribute)map.at(key)).Get<T>();
  }
  static const std::string GetStringAttr(const string &key,
                                         const AttributeMap &map) {
    return ((Attribute)map.at(key)).GetString();
  }

  static const bool HasAttr(const string &key, const AttributeMap &map) {
    return map.count(key) > 0;
  }

  template <typename T>
  static T *GetVarValue(const string &key, const VariableNameMap &var_map,
                        const Scope &scope) {
    PADDLE_MOBILE_ENFORCE(var_map.count(key) > 0,
                          "%s is not contained in var_map", key.c_str())
    auto var_vec = var_map.at(key);
    if (!var_vec.empty()) {
      auto var = scope.FindVar(var_vec[0]);
      return var->GetMutable<T>();
    } else {
      return nullptr;
    }
  }

  static Variable *GetVar(const string &key, const VariableNameMap &var_map,
                          const Scope &scope) {
    PADDLE_MOBILE_ENFORCE(var_map.count(key) > 0,
                          "%s is not contained in var_map", key.c_str())
    auto var_vec = var_map.at(key);
    if (!var_vec.empty()) {
      auto var = scope.FindVar(var_vec[0]);
      return var;
    } else {
      return nullptr;
    }
  }

  static std::string Getkey(const string &key, const VariableNameMap &var_map,
                            int index) {
    PADDLE_MOBILE_ENFORCE(var_map.count(key) > index,
                          "%s is not contained in var_map", key.c_str())
    auto var_vec = var_map.at(key);
    return var_vec[index];
  }

  template <typename T>
  static T *GetVarValue1(const string &key, const VariableNameMap &var_map,
                         const Scope &scope) {
    PADDLE_MOBILE_ENFORCE(var_map.count(key) > 0,
                          "%s is not contained in var_map", key.c_str())
    auto var_vec = var_map.at(key);
    if (!var_vec.empty()) {
      auto var = scope.FindVar(var_vec[1]);
      return var->GetMutable<T>();
    } else {
      return nullptr;
    }
  }

  template <typename T>
  static vector<T *> GetMultiVarValue(const string &key,
                                      const VariableNameMap &var_map,
                                      const Scope &scope) {
    auto var_vecs = var_map.at(key);
    assert(var_vecs.size() > 1);
    vector<T *> var_res;
    for (auto &var_vec : var_vecs) {
      auto var = scope.FindVar(var_vec);
      var_res.push_back(var->GetMutable<T>());
    }
    return var_res;
  }

  static vector<Variable *> GetMultiVar(const string &key,
                                        const VariableNameMap &var_map,
                                        const Scope &scope) {
    auto var_vecs = var_map.at(key);
    assert(var_vecs.size() > 1);
    vector<Variable *> var_res;
    for (auto &var_vec : var_vecs) {
      auto var = scope.FindVar(var_vec);
      var_res.push_back(var);
    }
    return var_res;
  }
};

/*template <>
LoDTensor *OpParam::GetVarValue(const string &key,
                                const VariableNameMap &var_map,
                                const Scope &scope) {
  PADDLE_MOBILE_ENFORCE(var_map.count(key) > 0,
                        "%s is not contained in var_map", key.c_str())
  auto var_vec = var_map.at(key);
  if (!var_vec.empty()) {
    auto var = scope.FindVar(var_vec[0]);
    return var->GetMutable<framework::TensorWrapper>()->InnerLoDTensor();
  } else {
    return nullptr;
  }
}
#ifdef PADDLE_MOBILE_CL

template <>
framework::CLImage *OpParam::GetVarValue(const string &key,
                                         const VariableNameMap &var_map,
                                         const Scope &scope) {
  PADDLE_MOBILE_ENFORCE(var_map.count(key) > 0,
                        "%s is not contained in var_map", key.c_str())
  auto var_vec = var_map.at(key);
  if (!var_vec.empty()) {
    auto var = scope.FindVar(var_vec[0]);
    return var->GetMutable<framework::TensorWrapper>()->InnerCLImage();
  } else {
    return nullptr;
  }
}
#endif*/

class ConvParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  ConvParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
            const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    filter_ = OpParam::FilterFrom<GType>(inputs, *scope);
    input_ = OpParam::InputFrom<GType>(inputs, *scope);
    if (outputs.count("Output")) {
      output_ = OpParam::OutputFrom<GType>(outputs, *scope);
    }
    strides_ = OpParam::GetAttr<vector<int>>("strides", attrs);
    paddings_ = OpParam::GetAttr<vector<int>>("paddings", attrs);
    dilations_ = OpParam::GetAttr<vector<int>>("dilations", attrs);
    groups = OpParam::GetAttr<int>("groups", attrs);
  }

  RType *Input() const { return input_; }

  RType *Filter() const { return filter_; }

  RType *Output() const { return output_; }
  RType *TransformedFilter() const { return transformed_filter_; }

  const vector<int> &Strides() const { return strides_; }

  const vector<int> &Paddings() const { return paddings_; }

  const vector<int> &Dilations() const { return dilations_; }

  enum ExecMode {
    EXEC_INVALID = 0,
    EXEC_GEMM_FLOAT,
    EXEC_DEPTHWISE3x3S1_FLOAT,
    EXEC_DEPTHWISE3x3S2_FLOAT,
    EXEC_WINOGRAD3X3_FLOAT,
    EXEC_WINOGRAD5X5_FLOAT,
    EXEC_DEPTHWISE5x5_FLOAT,
    EXEC_GEMM_INT8,
    EXEC_DEPTHWISE3x3_INT8,
    EXEC_DEPTHWISE5x5_INT8,
  };

  ExecMode &ExecMode() const { return exec_mode_; }

  const int &Groups() const { return groups; }

#ifdef PADDLE_MOBILE_CL
  int Offset() const { return offset_; }

  int SetOffset(int in_offset) { offset_ = in_offset; }

#endif

 public:
  GType *input_;
  GType *output_;
  GType *filter_;
  vector<int> strides_;
  vector<int> paddings_;
  vector<int> dilations_;
  GType *transformed_filter_;

  mutable enum ExecMode exec_mode_;
  int groups;

#ifdef PADDLE_MOBILE_CL
  int offset_;
#endif

#ifdef PADDLE_MOBILE_FPGA

 public:
  fpga::SplitConvArgs fpga_conv_args;

 public:
  const fpga::SplitConvArgs &FpgaArgs() const { return fpga_conv_args; }
  void SetFpgaArgs(const fpga::SplitConvArgs &args) { fpga_conv_args = args; }

 public:
  fpga::DWconvArgs fpga_dwconv_args;

 public:
  const fpga::DWconvArgs &FpgaDwconvArgs() const { return fpga_dwconv_args; }
  void SetFpgaArgs(const fpga::DWconvArgs &args) { fpga_dwconv_args = args; }
#endif
};

Print &operator<<(Print &printer, const ConvParam &conv_param);

class ElementwiseAddParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  ElementwiseAddParam(const VariableNameMap &inputs,
                      const VariableNameMap &outputs, const AttributeMap &attrs,
                      Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    input_y_ = InputYFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    axis_ = GetAttr<int>("axis", attrs);
  }

  RType *InputX() const { return input_x_; }

  RType *InputY() const { return input_y_; }

  RType *Out() const { return out_; }

  const int &Axis() const { return axis_; }

 private:
  GType *input_x_;
  GType *input_y_;
  GType *out_;
  int axis_;
#ifdef PADDLE_MOBILE_FPGA

 private:
  fpga::EWAddArgs fpga_EW_add_args;

 public:
  const fpga::EWAddArgs &FpgaArgs() const { return fpga_EW_add_args; }
  void SetFpgaArgs(const fpga::EWAddArgs &args) { fpga_EW_add_args = args; }

 public:
  Tensor float_input_x, float_out;

#endif
};

#ifdef ELEMENTWISEMUL_OP

class ElementwiseMulParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  ElementwiseMulParam(const VariableNameMap &inputs,
                      const VariableNameMap &outputs, const AttributeMap &attrs,
                      Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    input_y_ = InputYFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    axis_ = GetAttr<int>("axis", attrs);
  }

  RType *InputX() const { return input_x_; }

  RType *InputY() const { return input_y_; }

  RType *Out() const { return out_; }

  const int &Axis() const { return axis_; }

 private:
  GType *input_x_;
  GType *input_y_;
  GType *out_;
  int axis_;
#ifdef PADDLE_MOBILE_FPGA

 public:
  Tensor float_input_x, float_out;

#endif
};
#endif

#ifdef FUSION_ELEMENTWISEADDRELU_OP

using ElementwiseAddReluParam = ElementwiseAddParam;
#endif

#ifdef ELEMENTWISESUB_OP

class ElementwiseSubParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  ElementwiseSubParam(const VariableNameMap &inputs,
                      const VariableNameMap &outputs, const AttributeMap &attrs,
                      Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    input_y_ = InputYFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    axis_ = GetAttr<int>("axis", attrs);
  }

  RType *InputX() const { return input_x_; }

  RType *InputY() const { return input_y_; }

  RType *Out() const { return out_; }

  const int &Axis() const { return axis_; }

 private:
  GType *input_x_;
  GType *input_y_;
  GType *out_;
  int axis_;
};
#endif

#ifdef MUL_OP

class MulParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  MulParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
           const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    input_y_ = InputYFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    x_num_col_dims_ = GetAttr<int>("x_num_col_dims", attrs);
    y_num_col_dims_ = GetAttr<int>("y_num_col_dims", attrs);
  }

  RType *InputX() const { return input_x_; }

  RType *InputY() const { return input_y_; }

  RType *Out() const { return out_; }

  const int &XNumColDims() const { return x_num_col_dims_; }

  const int &YNumColDims() const { return y_num_col_dims_; }

 private:
  GType *input_x_;
  GType *input_y_;
  GType *out_;
  int x_num_col_dims_;
  int y_num_col_dims_;
};
#endif

#ifdef CONCAT_OP

class ConcatParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  ConcatParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
              const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    inputs_ = InputMultiFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    axis_ = GetAttr<int>("axis", attrs);
  }

  vector<GType *> Inputs() const { return inputs_; }

  RType *Out() const { return out_; }

  const int &Axis() const { return axis_; }

 private:
  vector<GType *> inputs_;
  GType *out_;
  int axis_;
#ifdef PADDLE_MOBILE_FPGA

 private:
  fpga::ConcatArgs fpga_concat_args;

 public:
  const fpga::ConcatArgs &FpgaArgs() const { return fpga_concat_args; }
  void SetFpgaArgs(const fpga::ConcatArgs &args) { fpga_concat_args = args; }
#endif
};
#endif

#ifdef SUM_OP

class SumParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  SumParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
           const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    inputs_vars_ = InputMultiVarsFrom(inputs, *scope);
    out_var_ = OutVarFrom(outputs, *scope);
    inputs_ = InputMultiFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
  }

  vector<Variable *> InputsVars() const { return inputs_vars_; }

  Variable *OutVar() const { return out_var_; }

  vector<GType *> Inputs() const { return inputs_; }

  RType *Out() const { return out_; }

 private:
  vector<Variable *> inputs_vars_;
  Variable *out_var_;
  vector<GType *> inputs_;
  GType *out_;
};
#endif

#ifdef LRN_OP

class LrnParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  LrnParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
           const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    mid_out_ = MidOutFrom<GType>(outputs, *scope);
    n_ = GetAttr<int>("n", attrs);
    alpha_ = GetAttr<float>("alpha", attrs);
    beta_ = GetAttr<float>("beta", attrs);
    k_ = GetAttr<float>("k", attrs);
    data_format_ = GetStringAttr("data_format", attrs);
  }

  RType *InputX() const { return input_x_; }

  RType *Out() const { return out_; }

  GType *MidOut() const { return mid_out_; }

  const int &N() const { return n_; }

  const float &Alpha() const { return alpha_; }

  const float &Beta() const { return beta_; }

  const float &K() const { return k_; }

  const string &DataFormat() const { return data_format_; }

 private:
  GType *input_x_;
  GType *out_;
  GType *mid_out_;
  int n_;
  float alpha_;
  float beta_;
  float k_;
  string data_format_;
};
#endif

#ifdef NORM_OP

class NormParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  NormParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
            const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    output_norm_ = OutputNormFrom<GType>(outputs, *scope);
    epsilon_ = GetAttr<float>("epsilon", attrs);
    axis_ = GetAttr<int>("axis", attrs);
  }

  RType *InputX() const { return input_x_; }

  RType *Out() const { return out_; }

  GType *OutputNorm() const { return output_norm_; }

  const float &Epsilon() const { return epsilon_; }

  const int &Axis() const { return axis_; }

 private:
  GType *input_x_;
  GType *out_;
  GType *output_norm_;
  float epsilon_;
  int axis_;
};
#endif

#ifdef BATCHNORM_OP

class BatchNormParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  BatchNormParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
                 const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    output_y_ = OutputYFrom<GType>(outputs, *scope);
    input_bias_ = InputBiasFrom<GType>(inputs, *scope);
    input_mean_ = InputMeanFrom<GType>(inputs, *scope);
    input_scale_ = InputScaleFrom<GType>(inputs, *scope);
    input_variance_ = InputVarianceFrom<GType>(inputs, *scope);
    epsilon_ = GetAttr<float>("epsilon", attrs);
    momentum_ = GetAttr<float>("momentum", attrs);
    //    is_test_ = GetAttr<bool>("is_test", attrs);
  }

  RType *InputX() const { return input_x_; }

  RType *OutputY() const { return output_y_; }

  RType *InputBias() const { return input_bias_; }

  RType *InputMean() const { return input_mean_; }

  RType *InputScale() const { return input_scale_; }

  RType *InputVariance() const { return input_variance_; }

  const float &Epsilon() const { return epsilon_; }

  const float &Momentum() const { return momentum_; }

  const bool &IsTest() const { return is_test_; }

  const string &DataFormat() const { return data_format_; }

  void SetNewScale(GType *new_scale) { new_scale_ = new_scale; }

  void SetNewBias(GType *new_bias) { new_bias_ = new_bias; }

  RType *NewScale() const { return new_scale_; }

  RType *NewBias() const { return new_bias_; }

 private:
  GType *input_x_;
  GType *output_y_;
  GType *input_bias_;
  GType *input_mean_;
  GType *input_scale_;
  GType *input_variance_;
  float epsilon_;
  float momentum_;
  bool is_test_;
  string data_format_;
  GType *new_bias_;
  GType *new_scale_;
};
#endif

#ifdef POOL_OP

class PoolParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  PoolParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
            const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_ = InputXFrom<GType>(inputs, *scope);

    output_ = OutFrom<GType>(outputs, *scope);
    pooling_type_ = GetStringAttr("pooling_type", attrs);
    ksize_ = GetAttr<vector<int>>("ksize", attrs);
    strides_ = GetAttr<vector<int>>("strides", attrs);
    paddings_ = GetAttr<vector<int>>("paddings", attrs);
    ceil_mode_ = GetAttr<bool>("ceil_mode", attrs);
    global_pooling_ = GetAttr<bool>("global_pooling", attrs);
  }

  RType *Input() const { return input_; }

  RType *Output() const { return output_; }

  const string &PoolingType() const { return pooling_type_; }

  const vector<int> &Ksize() const { return ksize_; }

  const vector<int> &Strides() const { return strides_; }

  const vector<int> &Paddings() const { return paddings_; }

  bool isCeilMode() const { return ceil_mode_; }

  bool isGlobalPooling() const { return global_pooling_; }

 private:
  GType *input_;
  GType *output_;
  string pooling_type_;
  vector<int> ksize_;
  vector<int> strides_;
  vector<int> paddings_;
  bool ceil_mode_;
  bool global_pooling_ = false;
#ifdef PADDLE_MOBILE_FPGA

 private:
  fpga::PoolingArgs fpga_pool_args;

 public:
  const fpga::PoolingArgs &FpgaArgs() const { return fpga_pool_args; }
  void SetFpgaArgs(const fpga::PoolingArgs &args) { fpga_pool_args = args; }
#endif
};
#endif

#ifdef PRIORBOX_OP

class PriorBoxParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  PriorBoxParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
                const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_ = InputFrom<GType>(inputs, *scope);
    input_image_ = InputImageFrom<GType>(inputs, *scope);
    output_boxes_ = OutputBoxesFrom<GType>(outputs, *scope);
    output_variances_ = OutputVariancesFrom<GType>(outputs, *scope);
    min_sizes_ = GetAttr<vector<float>>("min_sizes", attrs);
    max_sizes_ = GetAttr<vector<float>>("max_sizes", attrs);
    aspect_ratios_ = GetAttr<vector<float>>("aspect_ratios", attrs);
    variances_ = GetAttr<vector<float>>("variances", attrs);

    if (HasAttr("min_max_aspect_ratios_order", attrs)) {
      min_max_aspect_ratios_order_ =
          GetAttr<bool>("min_max_aspect_ratios_order", attrs);
    } else {
      min_max_aspect_ratios_order_ = false;
    }
    flip_ = GetAttr<bool>("flip", attrs);
    clip_ = GetAttr<bool>("clip", attrs);
    step_w_ = GetAttr<float>("step_w", attrs);
    step_h_ = GetAttr<float>("step_h", attrs);
    offset_ = GetAttr<float>("offset", attrs);
  }
  RType *Input() const { return input_; }

  RType *InputImage() const { return input_image_; }

  RType *OutputBoxes() const { return output_boxes_; }

  RType *OutputVariances() const { return output_variances_; }

  const vector<float> &MinSizes() const { return min_sizes_; }

  const vector<float> &MaxSizes() const { return max_sizes_; }

  const vector<float> &AspectRatios() const { return aspect_ratios_; }

  const vector<float> &Variances() const { return variances_; }

  const bool &Flip() const { return flip_; }

  const bool &Clip() const { return clip_; }

  const float &StepW() const { return step_w_; }

  const float &StepH() const { return step_h_; }

  const float &Offset() const { return offset_; }

  const bool &MinMaxAspectRatiosOrder() const {
    return min_max_aspect_ratios_order_;
  }

 private:
  GType *input_;
  GType *input_image_;
  GType *output_boxes_;
  GType *output_variances_;
  vector<float> min_sizes_;
  vector<float> max_sizes_;
  vector<float> aspect_ratios_;
  vector<float> variances_;
  bool flip_;
  bool clip_;
  float step_w_;
  float step_h_;
  float offset_;
  bool min_max_aspect_ratios_order_;
};
#endif

#ifdef BOXCODER_OP

class BoxCoderParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  BoxCoderParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
                const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_priorbox_ = InputPriorBoxFrom<GType>(inputs, *scope);
    input_priorboxvar_ = InputPriorBoxVarFrom<GType>(inputs, *scope);
    input_targetbox_ = InputTargetBoxFrom<GType>(inputs, *scope);
    output_box_ = OutputBoxFrom<GType>(outputs, *scope);
    code_type_ = GetStringAttr("code_type", attrs);
  }
  RType *InputPriorBox() const { return input_priorbox_; }

  RType *InputPriorBoxVar() const { return input_priorboxvar_; }

  RType *InputTargetBox() const { return input_targetbox_; }

  RType *OutputBox() const { return output_box_; }

  const std::string &CodeType() const { return code_type_; }

 private:
  GType *input_priorbox_;
  GType *input_priorboxvar_;
  GType *input_targetbox_;
  GType *output_box_;
  std::string code_type_;
};
#endif

#ifdef SOFTMAX_OP

class SoftmaxParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  SoftmaxParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
               const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
  }
  RType *InputX() const { return input_x_; }
  RType *Out() const { return out_; }

 private:
  GType *input_x_;
  GType *out_;

#ifdef PADDLE_MOBILE_FPGA

 private:
  std::shared_ptr<GType> float_input_x_;
  fpga::BypassArgs fpga_bypass_args;

 public:
  GType *FloatInput() const {
    return float_input_x_ == nullptr ? input_x_ : float_input_x_.get();
  }
  void SetFloatInput(LoDTensor *input) { float_input_x_.reset(input); }
  const fpga::BypassArgs &FpgaArgs() const { return fpga_bypass_args; }
  void SetFpgaArgs(const fpga::BypassArgs &args) { fpga_bypass_args = args; }
#endif
};
#endif

#ifdef SIGMOID_OP

class SigmoidParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  SigmoidParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
               const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
  }
  RType *InputX() const { return input_x_; }
  RType *Out() const { return out_; }

 private:
  GType *input_x_;
  GType *out_;
#ifdef PADDLE_MOBILE_FPGA

 private:
  fpga::BypassArgs fpga_bypass_args;

 public:
  const fpga::BypassArgs &FpgaArgs() const { return fpga_bypass_args; }
  void SetFpgaArgs(const fpga::BypassArgs &args) { fpga_bypass_args = args; }
#endif
};
#endif

#ifdef MULTICLASSNMS_OP

class MultiClassNMSParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  MultiClassNMSParam(const VariableNameMap &inputs,
                     const VariableNameMap &outputs, const AttributeMap &attrs,
                     Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_bboxes_ = InputBBoxesFrom<GType>(inputs, *scope);
    input_scores_ = InputScoresFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    background_label_ = GetAttr<int>("background_label", attrs);
    nms_top_k_ = GetAttr<int>("nms_top_k", attrs);
    keep_top_k_ = GetAttr<int>("keep_top_k", attrs);
    nms_threshold_ = GetAttr<float>("nms_threshold", attrs);
    nms_eta_ = GetAttr<float>("nms_eta", attrs);
    score_threshold_ = GetAttr<float>("score_threshold", attrs);
  }

  RType *InputBBoxes() const { return input_bboxes_; }

  RType *InputScores() const { return input_scores_; }

  RType *Out() const { return out_; }

  const int &BackGroundLabel() const { return background_label_; }

  const int &NMSTopK() const { return nms_top_k_; }

  const int &KeepTopK() const { return keep_top_k_; }

  const float &NMSThreshold() const { return nms_threshold_; }

  const float &NMSEta() const { return nms_eta_; }

  const float &ScoreThreshold() const { return score_threshold_; }

 private:
  GType *input_bboxes_;
  GType *input_scores_;
  GType *out_;
  int background_label_;
  int nms_top_k_;
  int keep_top_k_;
  float nms_threshold_;
  float nms_eta_;
  float score_threshold_;
};
#endif

#ifdef POLYGONBOXTRANSFORM_OP

class PolygonBoxTransformParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  PolygonBoxTransformParam(const VariableNameMap &inputs,
                           const VariableNameMap &outputs,
                           const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_ = InputFrom<GType>(inputs, *scope);
    output_ = OutputFrom<GType>(outputs, *scope);
  }
  RType *Input() const { return input_; }
  RType *Output() const { return output_; }

 private:
  GType *input_;
  GType *output_;
};
#endif

class FeedParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  FeedParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
            const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<framework::TensorWrapperArray>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    col_ = GetAttr<int>("col", attrs);
    auto var = scope->FindVar("batch_size");
    batch_size = var->GetValue<int>();
  }
  framework::TensorWrapperArray *InputX() const { return input_x_; }
  RType *Out() const { return out_; }
  const int Col() const { return col_; }
  const int BatchSize() const { return batch_size; }

 private:
  framework::TensorWrapperArray *input_x_;
  GType *out_;
  int col_;
  int batch_size;
};

class FetchParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  FetchParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
             const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    out_ = OutFrom<framework::TensorWrapperArray>(outputs, *scope);
    col_ = GetAttr<int>("col", attrs);
  }

  RType *InputX() const { return input_x_; }
  framework::TensorWrapperArray *Out() const { return out_; }
  const int Col() const { return col_; }

 private:
  GType *input_x_;
  framework::TensorWrapperArray *out_;
  int col_;
#ifdef PADDLE_MOBILE_FPGA

 public:
  fpga::BypassArgs fpga_bypass_args;
#endif
};

#ifdef FILL_CONSTANT_OP

class FillConstantParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  FillConstantParam(const VariableNameMap &inputs,
                    const VariableNameMap &outputs, const AttributeMap &attrs,
                    Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    out_var_ = OutVarFrom(outputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    dtype_ = GetAttr<int>("dtype", attrs);
    shape_ = GetAttr<vector<int>>("shape", attrs);
    value_ = GetAttr<float>("value", attrs);
  }

  Variable *OutVar() const { return out_var_; }

  RType *Out() const { return out_; }

  const int &DataDtype() const { return dtype_; }

  const vector<int> &Shape() const { return shape_; }

  const float &Value() const { return value_; }

 private:
  Variable *out_var_;
  GType *out_;
  int dtype_;
  vector<int> shape_;
  float value_;
};
#endif

#ifdef TRANSPOSE_OP

class TransposeParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  TransposeParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
                 const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    axis_ = GetAttr<vector<int>>("axis", attrs);
  }

  RType *InputX() const { return input_x_; }

  RType *Out() const { return out_; }

  const vector<int> &Axis() const { return axis_; }

 private:
  GType *input_x_;
  GType *out_;
  vector<int> axis_;
};
#endif

#ifdef TRANSPOSE2_OP

class Transpose2Param : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  Transpose2Param(const VariableNameMap &inputs, const VariableNameMap &outputs,
                  const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    output_xshape_ = OutputXShapeFrom<GType>(outputs, *scope);
    axis_ = GetAttr<vector<int>>("axis", attrs);
  }

  RType *InputX() const { return input_x_; }

  RType *Out() const { return out_; }

  GType *OutputXShape() const { return output_xshape_; }

  const vector<int> &Axis() const { return axis_; }

 private:
  GType *input_x_;
  GType *out_;
  GType *output_xshape_;
  vector<int> axis_;
};
#endif

#ifdef LOOKUP_OP

class LookupParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  LookupParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
              const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_w_ = InputWFrom<GType>(inputs, *scope);
    input_ids_ = InputIdsFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    padding_idx_ = GetAttr<int64_t>("padding_idx", attrs);
  }

  RType *InputW() const { return input_w_; }
  RType *InputIds() const { return input_ids_; }
  RType *Out() const { return out_; }
  int64_t PaddingIdx() const { return padding_idx_; }

 private:
  GType *input_w_;
  GType *input_ids_;
  GType *out_;
  int64_t padding_idx_;
};
#endif

#ifdef CRF_OP

class CrfParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  //    {G_OP_TYPE_CRF, {{"Emission", "Transition", "Label"}, {"ViterbiPath"}}},

  CrfParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
           const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    // todo crf params
    input_emission_ = InputEmissionFrom<GType>(inputs, *scope);
    input_transition_ = InputTransitionFrom<GType>(inputs, *scope);
    input_label_ = InputLabelFrom<GType>(inputs, *scope);
    output_viterbipath_ = OutputViterbiPathFrom<GType>(outputs, *scope);
    //    padding_idx_ = GetAttr<int64_t>("padding_idx", attrs);
  }
  RType *InputEmission() const { return input_emission_; }
  RType *InputTransition() const { return input_transition_; }
  RType *InputLabel() const { return input_label_; }
  GType *outputVBP() const { return output_viterbipath_; }
  //  RType *InputIds() const { return input_ids_; }
  //  RType *Out() const { return out_->template getInner<RType,Dtype>(); }
  //  int64_t PaddingIdx() const { return padding_idx_; }

 private:
  GType *input_emission_;
  GType *input_transition_;
  GType *input_label_;
  GType *output_viterbipath_;

  //  GType *input_ids_;
  //  GType *out_;
  //  int64_t padding_idx_;
};
#endif

#ifdef RESHAPE_OP

class ReshapeParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  ReshapeParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
               const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    input_shape_ = InputShapeFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    shape_ = GetAttr<vector<int>>("shape", attrs);

    if (HasAttr("inplace", attrs)) {
      inplace_ = GetAttr<bool>("inplace", attrs);
    } else {
      inplace_ = false;
      DLOG << "ReshapeParam lost inplace params. maybe fluid updated";
    }
  }

  RType *InputX() const { return input_x_; }

  RType *InputShape() const { return input_shape_; }

  RType *Out() const { return out_; }

  const vector<int> &Shape() const { return shape_; }

  const bool &Inplace() const { return inplace_; }

 private:
  GType *input_x_;
  GType *input_shape_;
  GType *out_;
  vector<int> shape_;
  bool inplace_;
};
#endif

#ifdef RESHAPE2_OP

class Reshape2Param : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  Reshape2Param(const VariableNameMap &inputs, const VariableNameMap &outputs,
                const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    input_shape_ = InputShapeFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    output_xshape_ = OutputXShapeFrom<GType>(outputs, *scope);
    shape_ = GetAttr<vector<int>>("shape", attrs);
    if (HasAttr("inplace", attrs)) {
      inplace_ = GetAttr<bool>("inplace", attrs);
    } else {
      inplace_ = false;
    }
  }

  RType *InputX() const { return input_x_; }

  RType *InputShape() const { return input_shape_; }

  RType *Out() const { return out_; }

  GType *OutputXShape() const { return output_xshape_; }

  const vector<int> &Shape() const { return shape_; }

  const bool &Inplace() const { return inplace_; }

 private:
  GType *input_x_;
  GType *input_shape_;
  GType *out_;
  GType *output_xshape_;
  vector<int> shape_;
  bool inplace_;
};
#endif

#ifdef SCALE_OP

class ScaleParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  ScaleParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
             const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    scale_ = GetAttr<float>("scale", attrs);
    bias_ = GetAttr<float>("bias", attrs);
  }

  RType *InputX() const { return input_x_; }

  RType *Out() const { return out_; }

  const float Scale() const { return scale_; }

  const float Bias() const { return bias_; }

 private:
  GType *input_x_;
  GType *out_;
  float scale_;
  float bias_;
};
#endif

#ifdef SLICE_OP

class SliceParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  SliceParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
             const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_ = InputFrom<GType>(inputs, *scope);
    output_ = OutFrom<GType>(outputs, *scope);

    axes_ = GetAttr<std::vector<int>>("axes", attrs);
    starts_ = GetAttr<std::vector<int>>("starts", attrs);
    ends_ = GetAttr<std::vector<int>>("ends", attrs);
  }

 public:
  GType *input_;
  GType *output_;
  std::vector<int> axes_;
  std::vector<int> starts_;
  std::vector<int> ends_;
};
#endif

#ifdef RESIZE_OP

class ResizeParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  ResizeParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
              const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    input_shape_ = InputShapeFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    is_pyramid_test_ = GetAttr<bool>("is_pyramid_test", attrs);
    height_ = GetAttr<int>("height", attrs);
    width_ = GetAttr<int>("width", attrs);
    out_height_scale_ = GetAttr<float>("out_height_scale", attrs);
    out_width_scale_ = GetAttr<float>("out_width_scale", attrs);
  }

  RType *InputX() const { return input_x_; }

  RType *InputShape() const { return input_shape_; }

  RType *Out() const { return out_; }

  const bool &IsPyramidTest() const { return is_pyramid_test_; }

  const int &Height() const { return height_; }

  const int &Width() const { return width_; }

  const float &OutHeightScale() const { return out_height_scale_; }

  const float &OutWidthScale() const { return out_width_scale_; }

 private:
  GType *input_x_;
  GType *input_shape_;
  GType *out_;
  bool is_pyramid_test_;
  int height_;
  int width_;
  float out_height_scale_;
  float out_width_scale_;
};
#endif

#ifdef RELU_OP
/*
 * @b op 层实例化好这个 param 传递给 kernel 层使用
 * */

class ReluParamBase : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  ReluParamBase(const VariableNameMap &inputs, const VariableNameMap &outputs,
                const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
  }

  RType *InputX() const { return input_x_; }

  RType *Out() const { return out_; }

 private:
  GType *input_x_;
  GType *out_;
};

class ReluParam : public ReluParamBase {
 public:
  using ReluParamBase::ReluParamBase;

#ifdef PADDLE_MOBILE_CL
  framework::CLImage &getMidImage() { return midImage; }

 private:
  framework::CLImage midImage;
#endif
};

#endif
#ifdef TANH_OP

class TanhParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  TanhParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
            const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
  }
  RType *InputX() const { return input_x_; }
  RType *Out() const { return out_; }

 private:
  GType *input_x_;
  GType *out_;
#ifdef PADDLE_MOBILE_FPGA

 private:
  std::shared_ptr<GType> float_input_x_;
  fpga::BypassArgs fpga_bypass_args;

 public:
  GType *FloatInput() const {
    return float_input_x_ == nullptr ? input_x_ : float_input_x_.get();
  }
  void SetFloatInput(LoDTensor *input) { float_input_x_.reset(input); }
  const fpga::BypassArgs &FpgaArgs() const { return fpga_bypass_args; }
  void SetFpgaArgs(const fpga::BypassArgs &args) { fpga_bypass_args = args; }
#endif
};
#endif

#ifdef PRELU_OP

class PReluParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  PReluParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
             const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    DLOG << "PReluParam inputs before";
    input_x_ = InputXFrom<GType>(inputs, *scope);
    alpha_ = InputAlphaFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    mode_ = GetStringAttr("mode", attrs);
    DLOG << "PReluParam mode after" << mode_;
  }
  RType *InputX() const { return input_x_; }
  RType *InputAlpha() const { return alpha_; }
  RType *Out() const { return out_; }
  const std::string &Mode() const { return mode_; }

 private:
  GType *input_x_;
  GType *out_;
  GType *alpha_;
  std::string mode_;
};
#endif

class FusionFcParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  FusionFcParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
                const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    input_y_ = InputYFrom<GType>(inputs, *scope);
    input_z_ = InputZFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    x_num_col_dims_ = GetAttr<int>("x_num_col_dims", attrs);
    y_num_col_dims_ = GetAttr<int>("y_num_col_dims", attrs);
    axis_ = GetAttr<int>("axis", attrs);
  }
  RType *InputX() const { return input_x_; }

  RType *InputY() const { return input_y_; }

  RType *InputZ() const { return input_z_; }

  RType *Out() const { return out_; }

  const int &XNumColDims() const { return x_num_col_dims_; }

  const int &YNumColDims() const { return y_num_col_dims_; }

  const int &Axis() const { return axis_; }

 private:
  GType *input_x_;
  GType *input_y_;
  GType *input_z_;
  GType *out_;
  int x_num_col_dims_;
  int y_num_col_dims_;
  int axis_;

#ifdef PADDLE_MOBILE_FPGA
 private:  // NOLINT
  fpga::SplitConvArgs fpga_conv_args;

 public:
  const fpga::SplitConvArgs &FpgaArgs() const { return fpga_conv_args; }
  void SetFpgaArgs(const fpga::SplitConvArgs &args) { fpga_conv_args = args; }
#endif
};

#ifdef FUSION_FCRELU_OP
template <typename DeviceType>
using FusionFcReluParam = FusionFcParam;
#endif

class FusionConvAddParam : public ConvParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  FusionConvAddParam(const VariableNameMap &inputs,
                     const VariableNameMap &outputs, const AttributeMap &attrs,
                     Scope *scope)
      : ConvParam(inputs, outputs, attrs, scope) {
    bias_ = OpParam::InputYFrom<GType>(inputs, *scope);
    axis_ = OpParam::GetAttr<int>("axis", attrs);
    this->output_ = OpParam::OutFrom<GType>(outputs, *scope);
  }
  RType *Bias() const { return bias_; }

  const int &Axis() const { return axis_; }

 protected:
  GType *bias_;
  int axis_;
};

Print &operator<<(Print &printer, const FusionConvAddParam &conv_param);

#ifdef FUSION_CONVADDRELU_OP
class FusionConvAddReluParam : public FusionConvAddParam {
 public:
  FusionConvAddReluParam(const VariableNameMap &inputs,
                         const VariableNameMap &outputs,
                         const AttributeMap &attrs, Scope *scope)
      : FusionConvAddParam(inputs, outputs, attrs, scope) {}
};
#endif

#ifdef FUSION_CONVADDPRELU_OP

class FusionConvAddPReluParam : public ConvParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  FusionConvAddPReluParam(const VariableNameMap &inputs,
                          const VariableNameMap &outputs,
                          const AttributeMap &attrs, Scope *scope)
      : ConvParam(inputs, outputs, attrs, scope) {
    alpha_ = OpParam::InputAlphaFrom<GType>(inputs, *scope);
    mode_ = OpParam::GetStringAttr("mode", attrs);
    //    framework::DDim dims = alpha_->dims();
    bias_ = OpParam::InputYFrom<GType>(inputs, *scope);
    axis_ = OpParam::GetAttr<int>("axis", attrs);
    this->output_ = OpParam::OutFrom<GType>(outputs, *scope);
  }
  RType *InputAlpha() const { return alpha_; }
  const std::string &Mode() const { return mode_; }
  RType *Bias() const { return bias_; }
  const int &Axis() const { return axis_; }

 protected:
  GType *bias_;
  int axis_;
  GType *alpha_;
  std::string mode_;
};
#endif

#ifdef FUSION_CONVADDADDPRELU_OP

class FusionConvAddAddPReluParam : public ConvParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  FusionConvAddAddPReluParam(const VariableNameMap &inputs,
                             const VariableNameMap &outputs,
                             const AttributeMap &attrs, Scope *scope)
      : ConvParam(inputs, outputs, attrs, scope) {
    bias1_ = OpParam::InputYFrom1<GType>(inputs, *scope);
    alpha_ = OpParam::InputAlphaFrom<GType>(inputs, *scope);
    mode_ = OpParam::GetStringAttr("mode", attrs);
    bias_ = OpParam::InputYFrom<GType>(inputs, *scope);
    axis_ = OpParam::GetAttr<int>("axis", attrs);
    keyOutput_ = OpParam::Getkey("addOut", inputs, 0);
    keyX1_ = OpParam::Getkey("addX", inputs, 1);
    keyY1_ = OpParam::Getkey("Y", inputs, 1);
    if (keyX1_ == keyOutput_) {
      bias1_ = OpParam::InputYFrom1<GType>(inputs, *scope);
    } else if (keyY1_ == keyOutput_) {
      bias1_ = OpParam::InputXFrom1<GType>(inputs, *scope);
    }
    this->output_ = OpParam::OutFrom<GType>(outputs, *scope);
  }
  RType *InputAlpha() const { return alpha_; }
  const std::string &Mode() const { return mode_; }
  RType *Bias1() const { return bias1_; }

  RType *Bias() const { return bias_; }

  const int &Axis() const { return axis_; }

 protected:
  GType *bias_;
  int axis_;
  GType *alpha_;
  std::string mode_;
  GType *bias1_;
  std::string keyOutput_;
  std::string keyX1_;
  std::string keyY1_;
};
#endif

#ifdef FUSION_CONVADDBNRELU_OP

class FusionConvAddBNReluParam : public ConvParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  FusionConvAddBNReluParam(const VariableNameMap &inputs,
                           const VariableNameMap &outputs,
                           const AttributeMap &attrs, Scope *scope)
      : ConvParam(inputs, outputs, attrs, scope) {
    bias_ = OpParam::InputYFrom<GType>(inputs, *scope);
    axis_ = OpParam::GetAttr<int>("axis", attrs);
    input_bias_ = OpParam::InputBiasFrom<GType>(inputs, *scope);
    input_mean_ = OpParam::InputMeanFrom<GType>(inputs, *scope);
    input_scale_ = OpParam::InputScaleFrom<GType>(inputs, *scope);
    input_variance_ = OpParam::InputVarianceFrom<GType>(inputs, *scope);
    epsilon_ = OpParam::GetAttr<float>("epsilon", attrs);
    momentum_ = OpParam::GetAttr<float>("momentum", attrs);
    this->output_ = OpParam::OutFrom<GType>(outputs, *scope);
  }
  RType *Bias() const { return bias_; }

  const int &Axis() const { return axis_; }

  RType *InputBias() const { return input_bias_; }

  RType *InputMean() const { return input_mean_; }

  RType *InputScale() const { return input_scale_; }

  RType *InputVariance() const { return input_variance_; }

  const float &Epsilon() const { return epsilon_; }

  const float &Momentum() const { return momentum_; }

  void SetNewScale(GType *new_scale) { new_scale_ = new_scale; }
  void SetNewBias(GType *new_bias) { new_bias_ = new_bias; }

  RType *NewScale() const { return new_scale_; }

  RType *NewBias() const { return new_bias_; }

 protected:
  GType *bias_;
  int axis_;
  GType *input_bias_;
  GType *input_mean_;
  GType *input_scale_;
  GType *input_variance_;
  float epsilon_;
  float momentum_;
  GType *new_bias_;
  GType *new_scale_;
};
#endif

#ifdef FUSION_CONVBNADDRELU_OP

class FusionConvBNAddReluParam : public ConvParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  FusionConvBNAddReluParam(const VariableNameMap &inputs,
                           const VariableNameMap &outputs,
                           const AttributeMap &attrs, Scope *scope)
      : ConvParam(inputs, outputs, attrs, scope) {
    bias_ = OpParam::InputYFrom<GType>(inputs, *scope);
    axis_ = OpParam::GetAttr<int>("axis", attrs);
    input_bias_ = OpParam::InputBiasFrom<GType>(inputs, *scope);
    input_mean_ = OpParam::InputMeanFrom<GType>(inputs, *scope);
    input_scale_ = OpParam::InputScaleFrom<GType>(inputs, *scope);
    input_variance_ = OpParam::InputVarianceFrom<GType>(inputs, *scope);
    epsilon_ = OpParam::GetAttr<float>("epsilon", attrs);
    momentum_ = OpParam::GetAttr<float>("momentum", attrs);
    keyBNY_ = OpParam::Getkey("BNY", inputs, 0);
    keyX_ = OpParam::Getkey("X", inputs, 0);
    keyY_ = OpParam::Getkey("Y", inputs, 0);
    if (keyX_ == keyBNY_) {
      bias_ = OpParam::InputYFrom<GType>(inputs, *scope);
    } else if (keyY_ == keyBNY_) {
      bias_ = OpParam::InputXFrom<GType>(inputs, *scope);
    }
    this->output_ = OpParam::OutFrom<GType>(outputs, *scope);
  }
  RType *Bias() const { return bias_; }

  const int &Axis() const { return axis_; }

  RType *InputBias() const { return input_bias_; }

  RType *InputMean() const { return input_mean_; }

  RType *InputScale() const { return input_scale_; }

  RType *InputVariance() const { return input_variance_; }

  const float &Epsilon() const { return epsilon_; }

  const float &Momentum() const { return momentum_; }

  void SetNewScale(GType *new_scale) { new_scale_ = new_scale; }

  void SetNewBias(GType *new_bias) { new_bias_ = new_bias; }

  RType *NewScale() const { return new_scale_; }

  RType *NewBias() const { return new_bias_; }

 protected:
  GType *bias_;
  int axis_;
  GType *input_bias_;
  GType *input_mean_;
  GType *input_scale_;
  GType *input_variance_;
  float epsilon_;
  float momentum_;
  GType *new_bias_;
  GType *new_scale_;
  std::string keyBNY_;
  std::string keyX_;
  std::string keyY_;
};
#endif

#ifdef FUSION_CONVBN_OP

class FusionConvBNParam : public ConvParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  FusionConvBNParam(const VariableNameMap &inputs,
                    const VariableNameMap &outputs, const AttributeMap &attrs,
                    Scope *scope)
      : ConvParam(inputs, outputs, attrs, scope) {
    input_bias_ = OpParam::InputBiasFrom<GType>(inputs, *scope);
    input_mean_ = OpParam::InputMeanFrom<GType>(inputs, *scope);
    input_scale_ = OpParam::InputScaleFrom<GType>(inputs, *scope);
    input_variance_ = OpParam::InputVarianceFrom<GType>(inputs, *scope);
    epsilon_ = OpParam::GetAttr<float>("epsilon", attrs);
    momentum_ = OpParam::GetAttr<float>("momentum", attrs);
    this->output_ = OpParam::OutputYFrom<GType>(outputs, *scope);
  }

  RType *InputBias() const { return input_bias_; }

  RType *InputMean() const { return input_mean_; }

  RType *InputScale() const { return input_scale_; }

  RType *InputVariance() const { return input_variance_; }

  const float &Epsilon() const { return epsilon_; }

  const float &Momentum() const { return momentum_; }

  void SetNewScale(GType *new_scale) { new_scale_ = new_scale; }

  void SetNewBias(GType *new_bias) { new_bias_ = new_bias; }

  RType *NewScale() const { return new_scale_; }

  RType *NewBias() const { return new_bias_; }

 protected:
  GType *input_bias_;
  GType *input_mean_;
  GType *input_scale_;
  GType *input_variance_;
  float epsilon_;
  float momentum_;
  GType *new_bias_;
  GType *new_scale_;
};
#endif

#ifdef FUSION_CONVADDBN_OP

class FusionConvAddBNParam : public ConvParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  FusionConvAddBNParam(const VariableNameMap &inputs,
                       const VariableNameMap &outputs,
                       const AttributeMap &attrs, Scope *scope)
      : ConvParam(inputs, outputs, attrs, scope) {
    bias_ = OpParam::InputYFrom<GType>(inputs, *scope);
    axis_ = OpParam::GetAttr<int>("axis", attrs);
    input_bias_ = OpParam::InputBiasFrom<GType>(inputs, *scope);
    input_mean_ = OpParam::InputMeanFrom<GType>(inputs, *scope);
    input_scale_ = OpParam::InputScaleFrom<GType>(inputs, *scope);
    input_variance_ = OpParam::InputVarianceFrom<GType>(inputs, *scope);
    epsilon_ = OpParam::GetAttr<float>("epsilon", attrs);
    momentum_ = OpParam::GetAttr<float>("momentum", attrs);
    this->output_ = OpParam::OutputYFrom<GType>(outputs, *scope);
  }
  RType *Bias() const { return bias_; }

  const int &Axis() const { return axis_; }

  RType *InputBias() const { return input_bias_; }

  RType *InputMean() const { return input_mean_; }

  RType *InputScale() const { return input_scale_; }

  RType *InputVariance() const { return input_variance_; }

  const float &Epsilon() const { return epsilon_; }

  const float &Momentum() const { return momentum_; }

  void SetNewScale(GType *new_scale) { new_scale_ = new_scale; }

  void SetNewBias(GType *new_bias) { new_bias_ = new_bias; }

  RType *NewScale() const { return new_scale_; }

  RType *NewBias() const { return new_bias_; }

 protected:
  GType *bias_;
  int axis_;
  GType *input_bias_;
  GType *input_mean_;
  GType *input_scale_;
  GType *input_variance_;
  float epsilon_;
  float momentum_;
  GType *new_bias_;
  GType *new_scale_;
};
#endif

#ifdef FUSION_DWCONVBNRELU_OP

class FusionDWConvBNReluParam : public ConvParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  FusionDWConvBNReluParam(const VariableNameMap &inputs,
                          const VariableNameMap &outputs,
                          const AttributeMap &attrs, Scope *scope)
      : ConvParam(inputs, outputs, attrs, scope) {
    input_bias_ = OpParam::InputBiasFrom<GType>(inputs, *scope);
    input_mean_ = OpParam::InputMeanFrom<GType>(inputs, *scope);
    input_scale_ = OpParam::InputScaleFrom<GType>(inputs, *scope);
    input_variance_ = OpParam::InputVarianceFrom<GType>(inputs, *scope);
    epsilon_ = OpParam::GetAttr<float>("epsilon", attrs);
    momentum_ = OpParam::GetAttr<float>("momentum", attrs);
    this->output_ = OpParam::OutFrom<GType>(outputs, *scope);
  }

  RType *InputBias() const { return input_bias_; }

  RType *InputMean() const { return input_mean_; }

  RType *InputScale() const { return input_scale_; }

  RType *InputVariance() const { return input_variance_; }

  const float &Epsilon() const { return epsilon_; }

  const float &Momentum() const { return momentum_; }

  void SetNewScale(GType *new_scale) { new_scale_ = new_scale; }

  void SetNewBias(GType *new_bias) { new_bias_ = new_bias; }

  RType *NewScale() const { return new_scale_; }

  RType *NewBias() const { return new_bias_; }

 protected:
  GType *input_bias_;
  GType *input_mean_;
  GType *input_scale_;
  GType *input_variance_;
  float epsilon_;
  float momentum_;
  GType *new_bias_;
  GType *new_scale_;
};

#endif

#ifdef FUSION_CONVBNRELU_OP

class FusionConvBNReluParam : public ConvParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  FusionConvBNReluParam(const VariableNameMap &inputs,
                        const VariableNameMap &outputs,
                        const AttributeMap &attrs, Scope *scope)
      : ConvParam(inputs, outputs, attrs, scope) {
    input_bias_ = OpParam::InputBiasFrom<GType>(inputs, *scope);
    input_mean_ = OpParam::InputMeanFrom<GType>(inputs, *scope);
    input_scale_ = OpParam::InputScaleFrom<GType>(inputs, *scope);
    input_variance_ = OpParam::InputVarianceFrom<GType>(inputs, *scope);
    epsilon_ = OpParam::GetAttr<float>("epsilon", attrs);
    momentum_ = OpParam::GetAttr<float>("momentum", attrs);
    this->output_ = OpParam::OutFrom<GType>(outputs, *scope);
  }

  RType *InputBias() const { return input_bias_; }

  RType *InputMean() const { return input_mean_; }

  RType *InputScale() const { return input_scale_; }

  RType *InputVariance() const { return input_variance_; }

  const float &Epsilon() const { return epsilon_; }

  const float &Momentum() const { return momentum_; }

  void SetNewScale(GType *new_scale) { new_scale_ = new_scale; }

  void SetNewBias(GType *new_bias) { new_bias_ = new_bias; }

  RType *NewScale() const { return new_scale_; }

  RType *NewBias() const { return new_bias_; }

 protected:
  GType *input_bias_;
  GType *input_mean_;
  GType *input_scale_;
  GType *input_variance_;
  float epsilon_;
  float momentum_;
  GType *new_bias_;
  GType *new_scale_;
};
#endif

#ifdef IM2SEQUENCE_OP

class Im2SequenceParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  Im2SequenceParam(const VariableNameMap &inputs,
                   const VariableNameMap &outputs, const AttributeMap &attrs,
                   Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    kernels_ = GetAttr<vector<int>>("kernels", attrs);
    strides_ = GetAttr<vector<int>>("strides", attrs);
    paddings_ = GetAttr<vector<int>>("paddings", attrs);
  }

  RType *Input() const { return input_x_; }

  RType *Output() const { return out_; }

  const vector<int> &Kernels() const { return kernels_; }

  const vector<int> &Strides() const { return strides_; }

  const vector<int> &Paddings() const { return paddings_; }

 private:
  GType *input_x_;
  GType *out_;
  vector<int> kernels_;
  vector<int> strides_;
  vector<int> paddings_;
};
#endif

#ifdef DROPOUT_OP

class DropoutParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  DropoutParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
               const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);

    dropout_prob_ = GetAttr<float>("dropout_prob", attrs);
  }

  RType *InputX() const { return input_x_; }

  RType *Out() const { return out_; }

  float DropoutProb() const { return dropout_prob_; }

 private:
  GType *input_x_;
  GType *out_;
  float dropout_prob_;
};
#endif

class ConvTransposeParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  ConvTransposeParam(const VariableNameMap &inputs,
                     const VariableNameMap &outputs, const AttributeMap &attrs,
                     Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    filter_ = FilterFrom<GType>(inputs, *scope);
    input_ = InputFrom<GType>(inputs, *scope);
    // output_ = OutputFrom<GType>(outputs, scope);
    if (outputs.count("Output")) {
      output_ = OpParam::OutputFrom<GType>(outputs, *scope);
    }
    strides_ = GetAttr<vector<int>>("strides", attrs);
    paddings_ = GetAttr<vector<int>>("paddings", attrs);
    dilations_ = GetAttr<vector<int>>("dilations", attrs);
    groups = GetAttr<int>("groups", attrs);
  }

  RType *Input() const { return input_; }

  RType *Filter() const { return filter_; }

  RType *Output() const { return output_; }

  const vector<int> &Strides() const { return strides_; }

  const vector<int> &Paddings() const { return paddings_; }

  const vector<int> &Dilations() const { return dilations_; }

  const int &Groups() const { return groups; }

  enum ExecMode {
    EXEC_INVALID = 0,
    EXEC_GEMM_FLOAT,
    EXEC_DECONV3X3_FLOAT,
    EXEC_DECONV4X4_FLOAT,
  };

  ExecMode &ExecMode() const { return exec_mode_; }

 private:
  GType *input_;
  GType *output_;
  GType *filter_;
  vector<int> strides_;
  vector<int> paddings_;
  vector<int> dilations_;
  int groups;
  mutable enum ExecMode exec_mode_;

#ifdef PADDLE_MOBILE_FPGA

 private:
  fpga::DeconvArgs fpga_conv_args;
  fpga::DWDeconvArgs fpga_DWDeconv_args;

 public:
  const fpga::DeconvArgs &FpgaArgs() const { return fpga_conv_args; }
  const fpga::DWDeconvArgs &FpgaDWDconvArgs() const {
    return fpga_DWDeconv_args;
  }
  void SetFpgaArgs(const fpga::DeconvArgs &args) { fpga_conv_args = args; }
  void SetFpgaArgs(const fpga::DWDeconvArgs &args) {
    fpga_DWDeconv_args = args;
  }
#endif
};

#ifdef FUSION_DECONVADD_OP

class FusionDeconvAddParam : public ConvTransposeParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  FusionDeconvAddParam(const VariableNameMap &inputs,
                       const VariableNameMap &outputs,
                       const AttributeMap &attrs, Scope *scope)
      : ConvTransposeParam(inputs, outputs, attrs, scope) {
    bias_ = OpParam::InputYFrom<GType>(inputs, *scope);
    axis_ = OpParam::GetAttr<int>("axis", attrs);
    output_ = OpParam::OutFrom<GType>(outputs, *scope);
  }
  RType *Bias() const { return bias_; }

  const int &Axis() const { return axis_; }

  RType *Output() const { return output_; }

 protected:
  GType *bias_;
  int axis_;
  GType *output_;
};
#endif

#ifdef FUSION_DECONVADDRELU_OP

using FusionDeconvAddReluParam = FusionDeconvAddParam;
#endif
#ifdef FUSION_DECONVADDBN_OP

class FusionDeconvAddBNParam : public ConvTransposeParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  FusionDeconvAddBNParam(const VariableNameMap &inputs,
                         const VariableNameMap &outputs,
                         const AttributeMap &attrs, Scope *scope)
      : ConvTransposeParam(inputs, outputs, attrs, scope) {
    output_ = OpParam::OutFrom<GType>(outputs, *scope);
    input_bias_ = OpParam::InputBiasFrom<GType>(inputs, *scope);
    input_mean_ = OpParam::InputMeanFrom<GType>(inputs, *scope);
    input_scale_ = OpParam::InputScaleFrom<GType>(inputs, *scope);
    input_variance_ = OpParam::InputVarianceFrom<GType>(inputs, *scope);
    epsilon_ = OpParam::GetAttr<float>("epsilon", attrs);
    momentum_ = OpParam::GetAttr<float>("momentum", attrs);
    //    is_test_ = OpParam::GetAttr<bool>("is_test", attrs);
  }
  RType *Output() const { return output_; }

  RType *InputBias() const { return input_bias_; }

  RType *InputMean() const { return input_mean_; }

  RType *InputScale() const { return input_scale_; }

  RType *InputVariance() const { return input_variance_; }

  const float &Epsilon() const { return epsilon_; }

  const float &Momentum() const { return momentum_; }

  const bool &IsTest() const { return is_test_; }

  void SetNewScale(RType *new_scale) { new_scale_ = new_scale; }

  void SetNewBias(RType *new_bias) { new_bias_ = new_bias; }

  RType *NewScale() const { return new_scale_; }

  RType *NewBias() const { return new_bias_; }

 protected:
  RType *output_;
  RType *input_bias_;
  RType *input_mean_;
  RType *input_scale_;
  RType *input_variance_;
  float epsilon_;
  float momentum_;
  bool is_test_;
  RType *new_bias_;
  RType *new_scale_;
};
#endif
#ifdef FUSION_DECONVBNRELU_OP

class FusionDeconvBNReluParam : public ConvTransposeParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  FusionDeconvBNReluParam(const VariableNameMap &inputs,
                          const VariableNameMap &outputs,
                          const AttributeMap &attrs, Scope *scope)
      : ConvTransposeParam(inputs, outputs, attrs, scope) {
    output_ = OpParam::OutFrom<GType>(outputs, *scope);
    input_bias_ = OpParam::InputBiasFrom<GType>(inputs, *scope);
    input_mean_ = OpParam::InputMeanFrom<GType>(inputs, *scope);
    input_scale_ = OpParam::InputScaleFrom<GType>(inputs, *scope);
    input_variance_ = OpParam::InputVarianceFrom<GType>(inputs, *scope);
    epsilon_ = OpParam::GetAttr<float>("epsilon", attrs);
    momentum_ = OpParam::GetAttr<float>("momentum", attrs);
  }
  RType *Output() const { return output_; }

  RType *InputBias() const { return input_bias_; }

  RType *InputMean() const { return input_mean_; }

  RType *InputScale() const { return input_scale_; }

  RType *InputVariance() const { return input_variance_; }

  const float &Epsilon() const { return epsilon_; }

  const float &Momentum() const { return momentum_; }

  const bool &IsTest() const { return is_test_; }

  void SetNewScale(RType *new_scale) { new_scale_ = new_scale; }

  void SetNewBias(RType *new_bias) { new_bias_ = new_bias; }

  RType *NewScale() const { return new_scale_; }

  RType *NewBias() const { return new_bias_; }

 protected:
  RType *output_;
  RType *input_bias_;
  RType *input_mean_;
  RType *input_scale_;
  RType *input_variance_;
  float epsilon_;
  float momentum_;
  bool is_test_;
  RType *new_bias_;
  RType *new_scale_;
};
#endif
#ifdef FUSION_DECONVADDBNRELU_OP

class FusionDeconvAddBNReluParam : public ConvTransposeParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  FusionDeconvAddBNReluParam(const VariableNameMap &inputs,
                             const VariableNameMap &outputs,
                             const AttributeMap &attrs, Scope *scope)
      : ConvTransposeParam(inputs, outputs, attrs, scope) {
    output_ = OpParam::OutFrom<GType>(outputs, *scope);
    input_bias_ = OpParam::InputBiasFrom<GType>(inputs, *scope);
    input_mean_ = OpParam::InputMeanFrom<GType>(inputs, *scope);
    input_scale_ = OpParam::InputScaleFrom<GType>(inputs, *scope);
    input_variance_ = OpParam::InputVarianceFrom<GType>(inputs, *scope);
    epsilon_ = OpParam::GetAttr<float>("epsilon", attrs);
    momentum_ = OpParam::GetAttr<float>("momentum", attrs);
    //    is_test_ = OpParam::GetAttr<bool>("is_test", attrs);
  }
  RType *Output() const { return output_; }

  RType *InputBias() const { return input_bias_; }

  RType *InputMean() const { return input_mean_; }

  RType *InputScale() const { return input_scale_; }

  RType *InputVariance() const { return input_variance_; }

  const float &Epsilon() const { return epsilon_; }

  const float &Momentum() const { return momentum_; }

  const bool &IsTest() const { return is_test_; }

  void SetNewScale(RType *new_scale) { new_scale_ = new_scale; }

  void SetNewBias(RType *new_bias) { new_bias_ = new_bias; }

  RType *NewScale() const { return new_scale_; }

  RType *NewBias() const { return new_bias_; }

 protected:
  RType *output_;
  RType *input_bias_;
  RType *input_mean_;
  RType *input_scale_;
  RType *input_variance_;
  float epsilon_;
  float momentum_;
  bool is_test_;
  RType *new_bias_;
  RType *new_scale_;
};
#endif

#ifdef FUSION_DECONVRELU_OP

using FusionDeconvReluParam = ConvTransposeParam;
#endif

#ifdef GRU_OP

class GruParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  /**
   *
   * @param inputs
   * @param outputs
   * @param attrs
   * @param scope
   * */
  GruParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
           const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_input_ = InputFrom<GType>(inputs, *scope);
    input_h0_ = InputH0From<GType>(inputs, *scope);
    input_bias_ = InputBiasFrom<GType>(inputs, *scope);
    input_weight_ = InputWeightFrom<GType>(inputs, *scope);

    output_batch_gate_ = OutputBatchGateFrom<GType>(outputs, *scope);
    output_batch_reset_hidden_prev_ =
        OutputBatchResetHiddenPrevFrom<GType>(outputs, *scope);
    output_batch_hidden_ = OutputBatchHiddenFrom<GType>(outputs, *scope);
    output_hidden_ = OutputHiddenFrom<GType>(outputs, *scope);
    activation_ = GetStringAttr("activation", attrs);
    gate_activation_ = GetStringAttr("gate_activation", attrs);
    is_reverse_ = GetAttr<bool>("is_reverse", attrs);
  }
  RType *InputInput() const { return input_input_; }
  RType *InputWeight() const { return input_weight_; }
  RType *InputH0() const { return input_h0_; }
  RType *InputBias() const { return input_bias_; }
  const std::string &Activation() const { return activation_; }
  const std::string &GateActivation() const { return gate_activation_; }
  const bool &IsReverse() const { return is_reverse_; }

  GType *OutBatchGate() const { return output_batch_gate_; }
  GType *OutBatchResetHiddenPrev() const {
    return output_batch_reset_hidden_prev_;
  }
  GType *OutBatchHidden() const { return output_batch_hidden_; }
  GType *OutHidden() const { return output_hidden_; }

 private:
  GType *input_input_;
  GType *input_h0_;
  GType *input_bias_;
  GType *input_weight_;

  GType *output_batch_gate_;
  GType *output_batch_reset_hidden_prev_;
  GType *output_batch_hidden_;
  GType *output_hidden_;
  std::string activation_;
  std::string gate_activation_;
  bool is_reverse_;
};
#endif

#ifdef GRU_UNIT_OP

class GruUnitParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  GruUnitParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
               const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_input_ = InputFrom<GType>(inputs, *scope);
    input_hidden_prev_ = InputHiddenPrevFrom<GType>(inputs, *scope);
    input_bias_ = InputBiasFrom<GType>(inputs, *scope);
    input_weight_ = InputWeightFrom<GType>(inputs, *scope);

    output_gate_ = OutputGateFrom<GType>(outputs, *scope);
    output_reset_hidden_prev_ =
        OutputResetHiddenPrevFrom<GType>(outputs, *scope);
    output_hidden_ = OutputHiddenFrom<GType>(outputs, *scope);
    activation_ = GetAttr<int>("activation", attrs);
    gate_activation_ = GetAttr<int>("gate_activation", attrs);
  }
  RType *InputInput() const { return input_input_; }
  RType *InputWeight() const { return input_weight_; }
  RType *InputHiddenPrev() const { return input_hidden_prev_; }
  RType *InputBias() const { return input_bias_; }
  const int &Activation() const { return activation_; }
  const int &GateActivation() const { return gate_activation_; }

  GType *OutGate() const { return output_gate_; }
  GType *OutResetHiddenPrev() const { return output_reset_hidden_prev_; }
  GType *OutHidden() const { return output_hidden_; }

 private:
  GType *input_input_;
  GType *input_hidden_prev_;
  GType *input_bias_;
  GType *input_weight_;

  GType *output_gate_;
  GType *output_reset_hidden_prev_;
  GType *output_hidden_;
  int activation_;
  int gate_activation_;
};
#endif

#ifdef FLATTEN_OP

class FlattenParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  FlattenParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
               const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    axis = GetAttr<int>("axis", attrs);
  }
  RType *InputX() const { return input_x_; }
  RType *Out() const { return out_; }
  const int &Axis() const { return axis; }

 private:
  GType *input_x_;
  GType *out_;
  int axis;
};
#endif

#ifdef SPLIT_OP

class SplitParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  SplitParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
             const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    outs_ = OutMultiFrom<GType>(outputs, *scope);
    axis = GetAttr<int>("axis", attrs);
    num = GetAttr<int>("num", attrs);
    sections = GetAttr<std::vector<int>>("sections", attrs);

    //    for (int i = 0; i < outs_.size(); ++i) {
    //      out_ts_.push_back(*scope.FindVar(outs_[i])->GetMutable());
    //    }
  }
  RType *InputX() const { return input_x_; }
  std::vector<GType *> Outs() const { return outs_; }
  int Axis() const { return axis; }
  int Num() const { return num; }
  std::vector<int> Sections() const { return sections; }
  //  std::vector<GType> OutTs() const { return out_ts_; }

 private:
  GType *input_x_;
  std::vector<GType *> outs_;
  int axis;
  int num;
  std::vector<int> sections;
  //  std::vector<GType> out_ts_;
#ifdef PADDLE_MOBILE_FPGA

 private:
  fpga::SplitArgs fpga_split_args;

 public:
  const fpga::SplitArgs &FpgaArgs() const { return fpga_split_args; }
  void SetFpgaArgs(const fpga::SplitArgs &args) { fpga_split_args = args; }
#endif
};
#endif

#ifdef BILINEAR_INTERP_OP

class BilinearInterpParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  BilinearInterpParam(const VariableNameMap &inputs,
                      const VariableNameMap &outputs, const AttributeMap &attrs,
                      Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    input_outsize_ = InputOutSizeFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
    out_h_ = GetAttr<int>("out_h", attrs);
    out_w_ = GetAttr<int>("out_w", attrs);
  }
  RType *InputX() const { return input_x_; }
  RType *InputOutPutSize() const { return input_outsize_; }
  RType *Out() const { return out_; }
  int OutH() const { return out_h_; }
  int OutW() const { return out_w_; }

 private:
  GType *input_x_;
  GType *input_outsize_;
  GType *out_;
  int out_h_;
  int out_w_;
};
#endif

#ifdef SHAPE_OP

class ShapeParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  ShapeParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
             const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_ = InputFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
  }
  RType *Input() const { return input_; }
  RType *Out() const { return out_; }

 private:
  GType *input_;
  GType *out_;
};
#endif

#ifdef TOP_K_OP

class TopKParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  TopKParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
            const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_ = OpParam::GetVarValue<GType>("X", inputs, *scope);
    output_ = OpParam::GetVarValue<GType>("Out", outputs, *scope);
    indices_ = OpParam::GetVarValue<GType>("Indices", outputs, *scope);
    k_ = OpParam::GetAttr<int>("k", attrs);
  }

 public:
  GType *input_;
  GType *output_;
  GType *indices_;
  int k_;
};
#endif  // TOP_K_OP

#ifdef CAST_OP

class CastParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  CastParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
            const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_ = OpParam::GetVarValue<GType>("X", inputs, *scope);
    output_ = OpParam::GetVarValue<GType>("Out", outputs, *scope);
    input_type_ = OpParam::GetAttr<int>("in_dtype", attrs);
    output_type_ = OpParam::GetAttr<int>("out_dtype", attrs);
  }

 public:
  GType *input_;
  GType *output_;
  int input_type_;
  int output_type_;
};
#endif  // CAST_OP

#ifdef QUANT_OP

class QuantizeParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  QuantizeParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
                const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_ = InputXFrom<GType>(inputs, *scope);
    output_ = OutFrom<GType>(outputs, *scope);
    // online
    // scale = max(abs(x))
    online_scale_ = OpParam::GetVarValue<GType>("OutScale", outputs, *scope);
    // offline
    if (inputs.count("InScale")) {
      offline_ = true;
      offline_scale_ = OpParam::GetVarValue<GType>("InScale", inputs, *scope);
    }
    // x = round(scale * x)
    if (OpParam::HasAttr("round_type", attrs)) {
      round_type_ = OpParam::GetAttr<RoundType>("round_type", attrs);
    }
  }

 public:
  // op input
  GType *input_;
  // op output
  GType *output_;
  GType *online_scale_;
  // quantize offline scale
  GType *offline_scale_;
  // if offine scale or not
  bool offline_ = false;
  // round method type
  // RoundType round_type_ = ROUND_NEAREST_AWAY_ZERO;
  RoundType round_type_ = ROUND_NEAREST_TOWARDS_ZERO;
};
#endif

#ifdef DEQUANT_OP

class DequantizeParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  DequantizeParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
                  const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_ = InputXFrom<GType>(inputs, *scope);
    output_ = OutFrom<GType>(outputs, *scope);
    activation_scale_ = OpParam::GetVarValue<GType>("Scale", inputs, *scope);
    // dequantization is performed as x = x / static_scale / online_scale
    if (OpParam::HasAttr("weight_scale", attrs)) {
      weight_scale_ = OpParam::GetAttr<float>("weight_scale", attrs);
    } else {
      weight_scale_ = OpParam::GetAttr<float>("max_range", attrs);
    }
  }

 public:
  // op input
  GType *input_;
  // op output
  GType *output_;
  GType *activation_scale_;
  float weight_scale_;
};
#endif

#if defined(FUSION_DEQUANT_BN_OP) || defined(FUSION_DEQUANT_ADD_BN_OP) || \
    defined(FUSION_DEQUANT_ADD_BN_RELU_OP) ||                             \
    defined(FUSION_DEQUANT_BN_RELU_OP) ||                                 \
    defined(FUSION_DEQUANT_ADD_BN_QUANT_OP) ||                            \
    defined(FUSION_DEQUANT_ADD_BN_RELU_QUANT_OP)

class FusionDequantBNParam : public DequantizeParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  FusionDequantBNParam(const VariableNameMap &inputs,
                       const VariableNameMap &outputs,
                       const AttributeMap &attrs, Scope *scope)
      : DequantizeParam(inputs, outputs, attrs, scope) {
    // batch norm params
    bn_mean_ = OpParam::GetVarValue<GType>("BNMean", inputs, *scope);
    bn_variance_ = OpParam::GetVarValue<GType>("BNVariance", inputs, *scope);
    bn_scale_ = OpParam::GetVarValue<GType>("BNScale", inputs, *scope);
    bn_bias_ = OpParam::GetVarValue<GType>("BNBias", inputs, *scope);
    epsilon_ = OpParam::GetAttr<float>("epsilon", attrs);
  }

 public:
  // batch norm
  GType *bn_mean_;
  GType *bn_variance_;
  GType *bn_scale_;
  GType *bn_bias_;
  float epsilon_;
};
#endif

#if defined(FUSION_DEQUANT_ADD_BN_RELU_OP) ||  \
    defined(FUSION_DEQUANT_ADD_BN_OP) ||       \
    defined(FUSION_DEQUANT_ADD_BN_QUANT_OP) || \
    defined(FUSION_DEQUANT_ADD_BN_RELU_QUANT_OP)

class FusionDequantAddBNParam : public FusionDequantBNParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  FusionDequantAddBNParam(const VariableNameMap &inputs,
                          const VariableNameMap &outputs,
                          const AttributeMap &attrs, Scope *scope)
      : FusionDequantBNParam(inputs, outputs, attrs, scope) {
    // element wise add params
    axis_ = OpParam::GetAttr<int>("axis", attrs);
    bias_ = OpParam::InputYFrom<GType>(inputs, *scope);
  }

 public:
  // elementwise add
  int axis_;
  GType *bias_;
};
#endif

#ifdef FUSION_DEQUANT_ADD_BN_QUANT_OP

class FusionDequantAddBNQuantParam : public FusionDequantAddBNParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  FusionDequantAddBNQuantParam(const VariableNameMap &inputs,
                               const VariableNameMap &outputs,
                               const AttributeMap &attrs, Scope *scope)
      : FusionDequantAddBNParam(inputs, outputs, attrs, scope) {
    // scale output
    online_scale_ = OpParam::GetVarValue<GType>("OutScale", outputs, *scope);
    // offline
    if (inputs.count("InScale")) {
      offline_ = true;
      offline_scale_ = OpParam::GetVarValue<GType>("InScale", inputs, *scope);
    }
    // x = round(scale * x)
    if (OpParam::HasAttr("round_type", attrs)) {
      round_type_ = OpParam::GetAttr<RoundType>("round_type", attrs);
    }
  }

 public:
  GType *online_scale_;
  // quantize offline scale
  GType *offline_scale_;
  // if offine scale or not
  bool offline_ = false;
  // round method type
  // RoundType round_type_ = ROUND_NEAREST_AWAY_ZERO;
  RoundType round_type_ = ROUND_NEAREST_TOWARDS_ZERO;
};
#endif

#ifdef SEQUENCE_EXPAND_OP

class SequenceExpandParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  SequenceExpandParam(const VariableNameMap &inputs,
                      const VariableNameMap &outputs, const AttributeMap &attrs,
                      Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    input_y_ = InputYFrom<GType>(inputs, *scope);
    output_ = OutFrom<GType>(outputs, *scope);
    ref_level_ = -1;
    if (OpParam::HasAttr("ref_level", attrs)) {
      ref_level_ = OpParam::GetAttr<int>("ref_level", attrs);
    }
  }

 public:
  GType *input_x_;
  GType *input_y_;
  GType *output_;
  int ref_level_;
};
#endif  // SEQUENCE_EXPAND_OP

#ifdef SEQUENCE_POOL_OP

class SequencePoolParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  SequencePoolParam(const VariableNameMap &inputs,
                    const VariableNameMap &outputs, const AttributeMap &attrs,
                    Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_ = InputXFrom<GType>(inputs, *scope);
    output_ = OutFrom<GType>(outputs, *scope);
    pool_type_ = "MAX";
    if (OpParam::HasAttr("pooltype", attrs)) {
      pool_type_ = OpParam::GetStringAttr("pooltype", attrs);
    }
  }

 public:
  GType *input_;
  GType *output_;
  std::string pool_type_;
};
#endif  // SEQUENCE_EXPAND_OP

#ifdef LOD_RESET_OP

class LodResetParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  LodResetParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
                const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    output_ = OutFrom<GType>(outputs, *scope);
    input_y_ = nullptr;
    if (inputs.count("Y")) {
      input_y_ = InputYFrom<GType>(inputs, *scope);
    } else {
      target_lod_ = OpParam::GetAttr<vector<int>>("target_lod", attrs);
    }
  }

 public:
  GType *input_x_;
  GType *input_y_;
  GType *output_;
  std::vector<int> target_lod_;
};
#endif  // LOD_RESET_OP

#ifdef LESS_THAN_OP

class CompareParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  CompareParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
               const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    input_y_ = InputYFrom<GType>(inputs, *scope);
    output_ = OutFrom<GType>(outputs, *scope);
    axis_ = OpParam::GetAttr<int>("axis", attrs);
  }

 public:
  GType *input_x_;
  GType *input_y_;
  GType *output_;
  int axis_;
};
#endif  // LESS_THAN_OP

#if defined(LOGICAL_AND_OP) || defined(LOGICAL_OR_OP) || defined(LOGICAL_XOR_OP)

class LogicalBinaryParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  LogicalBinaryParam(const VariableNameMap &inputs,
                     const VariableNameMap &outputs, const AttributeMap &attrs,
                     Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    input_y_ = InputYFrom<GType>(inputs, *scope);
    output_ = OutFrom<GType>(outputs, *scope);
  }

  RType *InputX() const { return input_x_; }
  RType *InputY() const { return input_y_; }
  RType *Out() const { return output_; }

 public:
  GType *input_x_;
  GType *input_y_;
  GType *output_;
};
#endif  // LOGICAL_AND_OP LOGICAL_OR_OP LOGICAL_XOR_OP

#ifdef LOGICAL_NOT_OP

class LogicalUnaryParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  LogicalUnaryParam(const VariableNameMap &inputs,
                    const VariableNameMap &outputs, const AttributeMap &attrs,
                    Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    output_ = OutFrom<GType>(outputs, *scope);
  }

  RType *InputX() const { return input_x_; }
  RType *Out() const { return output_; }

 public:
  GType *input_x_;
  GType *output_;
};
#endif  // LOGICAL_NOT_OP

#ifdef WRITE_TO_ARRAY_OP

class WriteToArrayParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  WriteToArrayParam(const VariableNameMap &inputs,
                    const VariableNameMap &outputs, const AttributeMap &attrs,
                    Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_ = OpParam::GetVarValue<GType>("X", inputs, *scope);
    index_ = OpParam::GetVarValue<GType>("I", inputs, *scope);
    output_ = OpParam::GetVarValue<std::vector<GType>>("Out", outputs, *scope);
  }

 public:
  GType *input_;
  GType *index_;
  std::vector<GType> *output_;
};
#endif

#ifdef READ_FROM_ARRAY_OP

class ReadFromArrayParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  ReadFromArrayParam(const VariableNameMap &inputs,
                     const VariableNameMap &outputs, const AttributeMap &attrs,
                     Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_ = OpParam::GetVarValue<std::vector<GType>>("X", inputs, *scope);
    index_ = OpParam::GetVarValue<GType>("I", inputs, *scope);
    output_ = OpParam::GetVarValue<GType>("Out", outputs, *scope);
  }

 public:
  std::vector<GType> *input_;
  GType *index_;
  GType *output_;
};
#endif

#ifdef IS_EMPTY_OP

class IsEmptyParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  IsEmptyParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
               const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    output_ = OutFrom<GType>(outputs, *scope);
  }

  RType *InputX() const { return input_x_; }
  RType *Out() const { return output_; }

 public:
  GType *input_x_;
  GType *output_;
};
#endif  // IS_EMPTY_OP

#ifdef INCREMENT_OP

class IncrementParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  IncrementParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
                 const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    output_ = OutFrom<GType>(outputs, *scope);
    step_ = OpParam::GetAttr<float>("step", attrs);
  }

  RType *InputX() const { return input_x_; }
  RType *Out() const { return output_; }
  float Step() const { return step_; }

 public:
  GType *input_x_;
  GType *output_;
  float step_;
};
#endif  // INCREMENT_OP
#ifdef PAD2D_OP

class Pad2dParam : public OpParam {
  typedef typename DtypeTensorTrait::gtype GType;
  typedef typename DtypeTensorTrait::rtype RType;

 public:
  Pad2dParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
             const AttributeMap &attrs, Scope *scope)
      : OpParam(inputs, outputs, attrs, scope) {
    input_x_ = InputXFrom<GType>(inputs, *scope);
    out_ = OutFrom<GType>(outputs, *scope);
  }
  RType *InputX() const { return input_x_; }
  RType *Out() const { return out_; }

 private:
  RType *input_x_;
  RType *out_;
};
#endif

}  // namespace operators
}  // namespace paddle_mobile

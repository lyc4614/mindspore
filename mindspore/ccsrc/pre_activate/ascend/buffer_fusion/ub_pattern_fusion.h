/**
 * Copyright 2019 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MINDSPORE_CCSRC_PRE_ACTIVATE_ASCEND_BUFFER_FUSION_UB_PATTERN_FUSION_H_
#define MINDSPORE_CCSRC_PRE_ACTIVATE_ASCEND_BUFFER_FUSION_UB_PATTERN_FUSION_H_
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "ir/anf.h"
#include "pre_activate/common/pass.h"
#include "pre_activate/common/fusion_id_allocator.h"
#include "device/kernel_info.h"
#include "kernel/kernel.h"
#include "session/kernel_graph.h"
#include "pre_activate/ascend/buffer_fusion/buffer_fusion.h"

namespace mindspore {
namespace opt {
using FusedNodeRecord = std::vector<std::unordered_set<AnfNodePtr>>;

class UbPatternFusion : public Pass {
 public:
  UbPatternFusion() : Pass("TbeBufferFusion") {}
  ~UbPatternFusion() override = default;
  bool Run(const FuncGraphPtr &graph) override;

 private:
  void GetBufferFusionInfo(session::KernelGraph *kernel_graph,
                           std::unordered_map<int32_t, BufferFusionInfo_t> *buffer_fusion_infos) const;
  bool ReplaceFusionOp(std::unordered_map<int32_t, BufferFusionInfo_t> *buffer_fusion_infos, int32_t fusion_id,
                       const kernel::KernelModPtr &kernel_ptr, session::KernelGraph *kernel_graph) const;
  bool FuseBufferFusionPattern(session::KernelGraph *kernel_graph) const;
};
}  // namespace opt
}  // namespace mindspore

#endif  // MINDSPORE_CCSRC_PRE_ACTIVATE_ASCEND_BUFFER_FUSION_UB_PATTERN_FUSION_H_

/*
 * SPDX-FileCopyrightText: Copyright (c) 2022-2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
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

#include "holoscan/core/resource.hpp"

#include "holoscan/core/component_spec.hpp"

namespace holoscan {

void Resource::initialize() {
  Component::initialize();

  if (!spec_) {
    HOLOSCAN_LOG_ERROR("No component spec for Resource '{}'", name());
    return;
  }

  // Set arguments
  auto& params = spec_->params();
  for (auto& arg : args_) {
    // Find if arg.name() is in spec.params()
    if (params.find(arg.name()) == params.end()) {
      HOLOSCAN_LOG_WARN("Argument '{}' not found in spec_->params()", arg.name());
      continue;
    }

    // Set arg.value() to spec.params()[arg.name()]
    auto& param_wrap = params[arg.name()];

    HOLOSCAN_LOG_TRACE("Resource '{}':: setting argument '{}'", name(), arg.name());

    ArgumentSetter::set_param(param_wrap, arg);
  }
}

YAML::Node Resource::to_yaml_node() const {
  YAML::Node node = Component::to_yaml_node();
  if (spec_) {
    node["spec"] = spec_->to_yaml_node();
  } else {
    node["spec"] = YAML::Null;
  }
  return node;
}

}  // namespace holoscan

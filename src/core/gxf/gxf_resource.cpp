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

#include "holoscan/core/gxf/gxf_resource.hpp"

#include <any>
#include <functional>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <utility>

#include "holoscan/core/component_spec.hpp"
#include "holoscan/core/executor.hpp"
#include "holoscan/core/fragment.hpp"

namespace holoscan::gxf {

GXFResource::GXFResource(const std::string& name, nvidia::gxf::Component* component) {
  id_ = component->cid();
  name_ = name;
  gxf_context_ = component->context();
  gxf_eid_ = component->eid();
  gxf_cid_ = component->cid();
  GxfComponentType(gxf_context_, gxf_cid_, &gxf_tid_);
  gxf_cname_ = name;
  gxf_cptr_ = component;
}

void GXFResource::initialize() {
  Resource::initialize();
  gxf_context_ = fragment()->executor().context();

  gxf_result_t code;
  // Create Entity for this Resource (without name so that new name is created) if gxf_eid_ is not
  // set.
  if (gxf_eid_ == 0) {
    const GxfEntityCreateInfo entity_create_info = {nullptr, GXF_ENTITY_CREATE_PROGRAM_BIT};
    code = GxfCreateEntity(gxf_context_, &entity_create_info, &gxf_eid_);
  }

  // Set GXF component name
  gxf_cname(name());

  GXFComponent::gxf_initialize();

  // Set GXF component ID as the component ID
  id_ = gxf_cid_;

  if (!spec_) {
    HOLOSCAN_LOG_ERROR("No component spec for GXFResource '{}'", name());
    return;
  }

  // Set Handler parameters
  for (auto& [key, param_wrap] : spec_->params()) {
    code = ::holoscan::gxf::GXFParameterAdaptor::set_param(
        gxf_context_, gxf_cid_, key.c_str(), param_wrap);
    // TODO: handle error
    HOLOSCAN_LOG_TRACE("GXFResource '{}':: setting GXF parameter '{}'", name(), key);
  }
  (void)code;
}

}  // namespace holoscan::gxf

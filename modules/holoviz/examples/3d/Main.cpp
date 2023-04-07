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

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <stdlib.h>
#include <chrono>
#include <memory>
#include <thread>

#include <holoviz/holoviz.hpp>

namespace viz = holoscan::viz;

bool unlimited_fps = false;
float fps = 15.f;

void tick() {
  viz::Begin();

  viz::BeginGeometryLayer();

  {
    const float data[]{
        // clang-format off
        0.1f, 0.1f, 0.1f,
        -0.1f, 0.1f, 0.1f,
        0.1f, -0.1f, 0.1f,
        -0.1f, -0.1f, 0.1f,
        0.1f, 0.1f, -0.1f,
        -0.1f, 0.1f, -0.1f,
        0.1f, -0.1f, -0.1f,
        -0.1f, -0.1f, -0.1f,
        // clang-format on
    };
    viz::Color(1.f, 0.f, 0.f, 1.f);
    viz::PointSize(5.f);
    viz::Primitive(viz::PrimitiveTopology::POINT_LIST_3D, 8, sizeof(data) / sizeof(data[0]), data);
  }

  {
    const float data[]{
        // clang-format off
        0.0f, 0.0f, 0.0f, 
        0.2f, 0.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 
        0.0f, 0.2f, 0.0f, 

        0.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 0.2f,
        // clang-format on
    };
    viz::Color(0.f, 1.f, 0.f, 1.f);
    viz::LineWidth(3.f);
    viz::Primitive(viz::PrimitiveTopology::LINE_LIST_3D, 3, sizeof(data) / sizeof(data[0]), data);
  }

  {
    const float data[]{
        // clang-format off
        -0.3f, -0.3f, 0.0f,
        -0.3f, 0.3f, 0.0f,
        0.3f, 0.3f, 0.0f,
        0.3f, -0.3f, 0.0f,
        -0.3f, -0.3f, 0.0f,
        // clang-format on
    };
    viz::Color(1.f, 1.f, 1.f, 1.f);
    viz::LineWidth(5.f);
    viz::Primitive(viz::PrimitiveTopology::LINE_STRIP_3D, 4, sizeof(data) / sizeof(data[0]), data);
  }

  {
    const float data[]{
        // clang-format off
        0.0f, 0.0f, 0.0f,
        0.2f, 0.0f, 0.0f,
        0.0f, 0.0f, -0.2f,

        0.0f, 0.0f, 0.0f,
        -0.2f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.2f,
        // clang-format on
    };
    viz::Color(0.f, 0.f, 1.f, 1.f);
    viz::Primitive(
        viz::PrimitiveTopology::TRIANGLE_LIST_3D, 2, sizeof(data) / sizeof(data[0]), data);
  }

  viz::EndLayer();

  viz::End();
}

int main(int argc, char** argv) {
  ImGui::CreateContext();
  viz::ImGuiSetCurrentContext(ImGui::GetCurrentContext());

  viz::Init(1024, 768, "Holoviz 3D Example");

  while (!viz::WindowShouldClose()) {
    if (!viz::WindowIsMinimized()) {
      tick();
      if (!unlimited_fps) {
        std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(1000.f / fps));
      }
    }
  }

  viz::Shutdown();

  return EXIT_SUCCESS;
}

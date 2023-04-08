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

#ifndef HOLOSCAN_VIZ_HOLOVIZ_VIEW_HPP
#define HOLOSCAN_VIZ_HOLOVIZ_VIEW_HPP

#include <array>
#include <cstdint>
#include <optional>

namespace holoscan::viz {

/**
 * Camera pose and perspective projection for a view.
 */
struct Camera {
  std::array<float, 16> view_matrix_col_major;
  std::array<float, 16> projection_matrix_col_major;
};

/**
 * Describes a view for which a layer can be rendered.
 */
struct View {
  std::array<uint32_t, 2> viewport_offset;
  std::array<uint32_t, 2> viewport_size;

  // The pose and perspective projection used to render 3D content for this
  // view, if specified; else the window's default camera is used.
  std::optional<Camera> camera;
};

}  // namespace holoscan::viz

#endif /* HOLOSCAN_VIZ_HOLOVIZ_VIEW_HPP */

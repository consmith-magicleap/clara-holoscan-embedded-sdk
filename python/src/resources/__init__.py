# SPDX-FileCopyrightText: Copyright (c) 2022 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
"""This module provides a Python API to underlying C++ API Resources.

.. autosummary::

    holoscan.resources.Allocator
    holoscan.resources.BlockMemoryPool
    holoscan.resources.CudaStreamPool
    holoscan.resources.DoubleBufferReceiver
    holoscan.resources.DoubleBufferTransmitter
    holoscan.resources.MemoryStorageType
    holoscan.resources.Receiver
    holoscan.resources.StdComponentSerializer
    holoscan.resources.Transmitter
    holoscan.resources.UnboundedAllocator
    holoscan.resources.VideoStreamSerializer
"""

from ._resources import (
    Allocator,
    BlockMemoryPool,
    CudaStreamPool,
    DoubleBufferReceiver,
    DoubleBufferTransmitter,
    MemoryStorageType,
    Receiver,
    StdComponentSerializer,
    Transmitter,
    UnboundedAllocator,
    VideoStreamSerializer,
)

__all__ = [
    "Allocator",
    "BlockMemoryPool",
    "CudaStreamPool",
    "DoubleBufferReceiver",
    "DoubleBufferTransmitter",
    "MemoryStorageType",
    "Receiver",
    "StdComponentSerializer",
    "Transmitter",
    "UnboundedAllocator",
    "VideoStreamSerializer",
]

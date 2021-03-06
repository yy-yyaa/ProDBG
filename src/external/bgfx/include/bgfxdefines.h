/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BGFX_DEFINES_H_HEADER_GUARD
#define BGFX_DEFINES_H_HEADER_GUARD

///
#define BGFX_STATE_RGB_WRITE             UINT64_C(0x0000000000000001)
#define BGFX_STATE_ALPHA_WRITE           UINT64_C(0x0000000000000002)
#define BGFX_STATE_DEPTH_WRITE           UINT64_C(0x0000000000000004)

#define BGFX_STATE_DEPTH_TEST_LESS       UINT64_C(0x0000000000000010)
#define BGFX_STATE_DEPTH_TEST_LEQUAL     UINT64_C(0x0000000000000020)
#define BGFX_STATE_DEPTH_TEST_EQUAL      UINT64_C(0x0000000000000030)
#define BGFX_STATE_DEPTH_TEST_GEQUAL     UINT64_C(0x0000000000000040)
#define BGFX_STATE_DEPTH_TEST_GREATER    UINT64_C(0x0000000000000050)
#define BGFX_STATE_DEPTH_TEST_NOTEQUAL   UINT64_C(0x0000000000000060)
#define BGFX_STATE_DEPTH_TEST_NEVER      UINT64_C(0x0000000000000070)
#define BGFX_STATE_DEPTH_TEST_ALWAYS     UINT64_C(0x0000000000000080)
#define BGFX_STATE_DEPTH_TEST_SHIFT      4
#define BGFX_STATE_DEPTH_TEST_MASK       UINT64_C(0x00000000000000f0)

#define BGFX_STATE_BLEND_ZERO            UINT64_C(0x0000000000001000)
#define BGFX_STATE_BLEND_ONE             UINT64_C(0x0000000000002000)
#define BGFX_STATE_BLEND_SRC_COLOR       UINT64_C(0x0000000000003000)
#define BGFX_STATE_BLEND_INV_SRC_COLOR   UINT64_C(0x0000000000004000)
#define BGFX_STATE_BLEND_SRC_ALPHA       UINT64_C(0x0000000000005000)
#define BGFX_STATE_BLEND_INV_SRC_ALPHA   UINT64_C(0x0000000000006000)
#define BGFX_STATE_BLEND_DST_ALPHA       UINT64_C(0x0000000000007000)
#define BGFX_STATE_BLEND_INV_DST_ALPHA   UINT64_C(0x0000000000008000)
#define BGFX_STATE_BLEND_DST_COLOR       UINT64_C(0x0000000000009000)
#define BGFX_STATE_BLEND_INV_DST_COLOR   UINT64_C(0x000000000000a000)
#define BGFX_STATE_BLEND_SRC_ALPHA_SAT   UINT64_C(0x000000000000b000)
#define BGFX_STATE_BLEND_FACTOR          UINT64_C(0x000000000000c000)
#define BGFX_STATE_BLEND_INV_FACTOR      UINT64_C(0x000000000000d000)
#define BGFX_STATE_BLEND_SHIFT           12
#define BGFX_STATE_BLEND_MASK            UINT64_C(0x000000000ffff000)

#define BGFX_STATE_BLEND_EQUATION_ADD    UINT64_C(0x0000000000000000)
#define BGFX_STATE_BLEND_EQUATION_SUB    UINT64_C(0x0000000010000000)
#define BGFX_STATE_BLEND_EQUATION_REVSUB UINT64_C(0x0000000020000000)
#define BGFX_STATE_BLEND_EQUATION_MIN    UINT64_C(0x0000000030000000)
#define BGFX_STATE_BLEND_EQUATION_MAX    UINT64_C(0x0000000040000000)
#define BGFX_STATE_BLEND_EQUATION_SHIFT  28
#define BGFX_STATE_BLEND_EQUATION_MASK   UINT64_C(0x00000003f0000000)

#define BGFX_STATE_BLEND_INDEPENDENT     UINT64_C(0x0000000400000000)

#define BGFX_STATE_CULL_CW               UINT64_C(0x0000001000000000)
#define BGFX_STATE_CULL_CCW              UINT64_C(0x0000002000000000)
#define BGFX_STATE_CULL_SHIFT            36
#define BGFX_STATE_CULL_MASK             UINT64_C(0x0000003000000000)

#define BGFX_STATE_ALPHA_REF_SHIFT       40
#define BGFX_STATE_ALPHA_REF_MASK        UINT64_C(0x0000ff0000000000)

#define BGFX_STATE_PT_TRISTRIP           UINT64_C(0x0001000000000000)
#define BGFX_STATE_PT_LINES              UINT64_C(0x0002000000000000)
#define BGFX_STATE_PT_LINESTRIP          UINT64_C(0x0003000000000000)
#define BGFX_STATE_PT_POINTS             UINT64_C(0x0004000000000000)
#define BGFX_STATE_PT_SHIFT              48
#define BGFX_STATE_PT_MASK               UINT64_C(0x0007000000000000)

#define BGFX_STATE_POINT_SIZE_SHIFT      52
#define BGFX_STATE_POINT_SIZE_MASK       UINT64_C(0x0ff0000000000000)

#define BGFX_STATE_MSAA                  UINT64_C(0x1000000000000000)

#define BGFX_STATE_RESERVED_MASK         UINT64_C(0xe000000000000000)

#define BGFX_STATE_NONE                  UINT64_C(0x0000000000000000)
#define BGFX_STATE_MASK                  UINT64_C(0xffffffffffffffff)
#define BGFX_STATE_DEFAULT (0 \
					| BGFX_STATE_RGB_WRITE \
					| BGFX_STATE_ALPHA_WRITE \
					| BGFX_STATE_DEPTH_TEST_LESS \
					| BGFX_STATE_DEPTH_WRITE \
					| BGFX_STATE_CULL_CW \
					| BGFX_STATE_MSAA \
					)

#define BGFX_STATE_ALPHA_REF(_ref)   ( ( (uint64_t)(_ref )<<BGFX_STATE_ALPHA_REF_SHIFT )&BGFX_STATE_ALPHA_REF_MASK)
#define BGFX_STATE_POINT_SIZE(_size) ( ( (uint64_t)(_size)<<BGFX_STATE_POINT_SIZE_SHIFT)&BGFX_STATE_POINT_SIZE_MASK)

///
#define BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA) (UINT64_C(0) \
					| ( ( (uint64_t)(_srcRGB)|( (uint64_t)(_dstRGB)<<4) )   ) \
					| ( ( (uint64_t)(_srcA  )|( (uint64_t)(_dstA  )<<4) )<<8) \
					)

#define BGFX_STATE_BLEND_EQUATION_SEPARATE(_rgb, _a) ( (uint64_t)(_rgb)|( (uint64_t)(_a)<<3) )

///
#define BGFX_STATE_BLEND_FUNC(_src, _dst)    BGFX_STATE_BLEND_FUNC_SEPARATE(_src, _dst, _src, _dst)
#define BGFX_STATE_BLEND_EQUATION(_equation) BGFX_STATE_BLEND_EQUATION_SEPARATE(_equation, _equation)

#define BGFX_STATE_BLEND_ADD         (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE,       BGFX_STATE_BLEND_ONE          ) )
#define BGFX_STATE_BLEND_ALPHA       (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA) )
#define BGFX_STATE_BLEND_DARKEN      (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE,       BGFX_STATE_BLEND_ONE          ) | BGFX_STATE_BLEND_EQUATION(BGFX_STATE_BLEND_EQUATION_MIN) )
#define BGFX_STATE_BLEND_LIGHTEN     (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE,       BGFX_STATE_BLEND_ONE          ) | BGFX_STATE_BLEND_EQUATION(BGFX_STATE_BLEND_EQUATION_MAX) )
#define BGFX_STATE_BLEND_MULTIPLY    (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_DST_COLOR, BGFX_STATE_BLEND_ZERO         ) )
#define BGFX_STATE_BLEND_NORMAL      (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE,       BGFX_STATE_BLEND_INV_SRC_ALPHA) )
#define BGFX_STATE_BLEND_SCREEN      (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE,       BGFX_STATE_BLEND_INV_SRC_COLOR) )
#define BGFX_STATE_BLEND_LINEAR_BURN (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_DST_COLOR, BGFX_STATE_BLEND_INV_DST_COLOR) | BGFX_STATE_BLEND_EQUATION(BGFX_STATE_BLEND_EQUATION_SUB) )

///
#define BGFX_STATE_BLEND_FUNC_RT_x(_src, _dst) (0 \
					| ( uint32_t( (_src)>>BGFX_STATE_BLEND_SHIFT) \
					| ( uint32_t( (_dst)>>BGFX_STATE_BLEND_SHIFT)<<4) ) \
					)

#define BGFX_STATE_BLEND_FUNC_RT_xE(_src, _dst, _equation) (0 \
					| BGFX_STATE_BLEND_FUNC_RT_x(_src, _dst) \
					| ( uint32_t( (_equation)>>BGFX_STATE_BLEND_EQUATION_SHIFT)<<8) \
					)

#define BGFX_STATE_BLEND_FUNC_RT_1(_src, _dst)  (BGFX_STATE_BLEND_FUNC_RT_x(_src, _dst)<< 0)
#define BGFX_STATE_BLEND_FUNC_RT_2(_src, _dst)  (BGFX_STATE_BLEND_FUNC_RT_x(_src, _dst)<<11)
#define BGFX_STATE_BLEND_FUNC_RT_3(_src, _dst)  (BGFX_STATE_BLEND_FUNC_RT_x(_src, _dst)<<22)

#define BGFX_STATE_BLEND_FUNC_RT_1E(_src, _dst, _equation) (BGFX_STATE_BLEND_FUNC_RT_xE(_src, _dst, _equation)<< 0)
#define BGFX_STATE_BLEND_FUNC_RT_2E(_src, _dst, _equation) (BGFX_STATE_BLEND_FUNC_RT_xE(_src, _dst, _equation)<<11)
#define BGFX_STATE_BLEND_FUNC_RT_3E(_src, _dst, _equation) (BGFX_STATE_BLEND_FUNC_RT_xE(_src, _dst, _equation)<<22)

///
#define BGFX_STENCIL_FUNC_REF_SHIFT      0
#define BGFX_STENCIL_FUNC_REF_MASK       UINT32_C(0x000000ff)
#define BGFX_STENCIL_FUNC_RMASK_SHIFT    8
#define BGFX_STENCIL_FUNC_RMASK_MASK     UINT32_C(0x0000ff00)

#define BGFX_STENCIL_TEST_LESS           UINT32_C(0x00010000)
#define BGFX_STENCIL_TEST_LEQUAL         UINT32_C(0x00020000)
#define BGFX_STENCIL_TEST_EQUAL          UINT32_C(0x00030000)
#define BGFX_STENCIL_TEST_GEQUAL         UINT32_C(0x00040000)
#define BGFX_STENCIL_TEST_GREATER        UINT32_C(0x00050000)
#define BGFX_STENCIL_TEST_NOTEQUAL       UINT32_C(0x00060000)
#define BGFX_STENCIL_TEST_NEVER          UINT32_C(0x00070000)
#define BGFX_STENCIL_TEST_ALWAYS         UINT32_C(0x00080000)
#define BGFX_STENCIL_TEST_SHIFT          16
#define BGFX_STENCIL_TEST_MASK           UINT32_C(0x000f0000)

#define BGFX_STENCIL_OP_FAIL_S_ZERO      UINT32_C(0x00000000)
#define BGFX_STENCIL_OP_FAIL_S_KEEP      UINT32_C(0x00100000)
#define BGFX_STENCIL_OP_FAIL_S_REPLACE   UINT32_C(0x00200000)
#define BGFX_STENCIL_OP_FAIL_S_INCR      UINT32_C(0x00300000)
#define BGFX_STENCIL_OP_FAIL_S_INCRSAT   UINT32_C(0x00400000)
#define BGFX_STENCIL_OP_FAIL_S_DECR      UINT32_C(0x00500000)
#define BGFX_STENCIL_OP_FAIL_S_DECRSAT   UINT32_C(0x00600000)
#define BGFX_STENCIL_OP_FAIL_S_INVERT    UINT32_C(0x00700000)
#define BGFX_STENCIL_OP_FAIL_S_SHIFT     20
#define BGFX_STENCIL_OP_FAIL_S_MASK      UINT32_C(0x00f00000)

#define BGFX_STENCIL_OP_FAIL_Z_ZERO      UINT32_C(0x00000000)
#define BGFX_STENCIL_OP_FAIL_Z_KEEP      UINT32_C(0x01000000)
#define BGFX_STENCIL_OP_FAIL_Z_REPLACE   UINT32_C(0x02000000)
#define BGFX_STENCIL_OP_FAIL_Z_INCR      UINT32_C(0x03000000)
#define BGFX_STENCIL_OP_FAIL_Z_INCRSAT   UINT32_C(0x04000000)
#define BGFX_STENCIL_OP_FAIL_Z_DECR      UINT32_C(0x05000000)
#define BGFX_STENCIL_OP_FAIL_Z_DECRSAT   UINT32_C(0x06000000)
#define BGFX_STENCIL_OP_FAIL_Z_INVERT    UINT32_C(0x07000000)
#define BGFX_STENCIL_OP_FAIL_Z_SHIFT     24
#define BGFX_STENCIL_OP_FAIL_Z_MASK      UINT32_C(0x0f000000)

#define BGFX_STENCIL_OP_PASS_Z_ZERO      UINT32_C(0x00000000)
#define BGFX_STENCIL_OP_PASS_Z_KEEP      UINT32_C(0x10000000)
#define BGFX_STENCIL_OP_PASS_Z_REPLACE   UINT32_C(0x20000000)
#define BGFX_STENCIL_OP_PASS_Z_INCR      UINT32_C(0x30000000)
#define BGFX_STENCIL_OP_PASS_Z_INCRSAT   UINT32_C(0x40000000)
#define BGFX_STENCIL_OP_PASS_Z_DECR      UINT32_C(0x50000000)
#define BGFX_STENCIL_OP_PASS_Z_DECRSAT   UINT32_C(0x60000000)
#define BGFX_STENCIL_OP_PASS_Z_INVERT    UINT32_C(0x70000000)
#define BGFX_STENCIL_OP_PASS_Z_SHIFT     28
#define BGFX_STENCIL_OP_PASS_Z_MASK      UINT32_C(0xf0000000)

#define BGFX_STENCIL_NONE                UINT32_C(0x00000000)
#define BGFX_STENCIL_MASK                UINT32_C(0xffffffff)
#define BGFX_STENCIL_DEFAULT             UINT32_C(0x00000000)

#define BGFX_STENCIL_FUNC_REF(_ref) ( (uint32_t(_ref)<<BGFX_STENCIL_FUNC_REF_SHIFT)&BGFX_STENCIL_FUNC_REF_MASK)
#define BGFX_STENCIL_FUNC_RMASK(_mask) ( (uint32_t(_mask)<<BGFX_STENCIL_FUNC_RMASK_SHIFT)&BGFX_STENCIL_FUNC_RMASK_MASK)

///
#define BGFX_CLEAR_NONE                  UINT16_C(0x0000)
#define BGFX_CLEAR_COLOR                 UINT16_C(0x0001)
#define BGFX_CLEAR_DEPTH                 UINT16_C(0x0002)
#define BGFX_CLEAR_STENCIL               UINT16_C(0x0004)
#define BGFX_CLEAR_DISCARD_COLOR_0       UINT16_C(0x0008)
#define BGFX_CLEAR_DISCARD_COLOR_1       UINT16_C(0x0010)
#define BGFX_CLEAR_DISCARD_COLOR_2       UINT16_C(0x0020)
#define BGFX_CLEAR_DISCARD_COLOR_3       UINT16_C(0x0040)
#define BGFX_CLEAR_DISCARD_COLOR_4       UINT16_C(0x0080)
#define BGFX_CLEAR_DISCARD_COLOR_5       UINT16_C(0x0100)
#define BGFX_CLEAR_DISCARD_COLOR_6       UINT16_C(0x0200)
#define BGFX_CLEAR_DISCARD_COLOR_7       UINT16_C(0x0400)
#define BGFX_CLEAR_DISCARD_DEPTH         UINT16_C(0x0800)
#define BGFX_CLEAR_DISCARD_STENCIL       UINT16_C(0x1000)

#define BGFX_CLEAR_DISCARD_COLOR_MASK (0 \
			| BGFX_CLEAR_DISCARD_COLOR_0 \
			| BGFX_CLEAR_DISCARD_COLOR_1 \
			| BGFX_CLEAR_DISCARD_COLOR_2 \
			| BGFX_CLEAR_DISCARD_COLOR_3 \
			| BGFX_CLEAR_DISCARD_COLOR_4 \
			| BGFX_CLEAR_DISCARD_COLOR_5 \
			| BGFX_CLEAR_DISCARD_COLOR_6 \
			| BGFX_CLEAR_DISCARD_COLOR_7 \
			)
#define BGFX_CLEAR_DISCARD_MASK (0 \
			| BGFX_CLEAR_DISCARD_COLOR_MASK \
			| BGFX_CLEAR_DISCARD_DEPTH \
			| BGFX_CLEAR_DISCARD_STENCIL \
			)

///
#define BGFX_DEBUG_NONE                  UINT32_C(0x00000000)
#define BGFX_DEBUG_WIREFRAME             UINT32_C(0x00000001)
#define BGFX_DEBUG_IFH                   UINT32_C(0x00000002)
#define BGFX_DEBUG_STATS                 UINT32_C(0x00000004)
#define BGFX_DEBUG_TEXT                  UINT32_C(0x00000008)

///
#define BGFX_BUFFER_NONE                 UINT8_C(0x00)
#define BGFX_BUFFER_COMPUTE_READ         UINT8_C(0x01)
#define BGFX_BUFFER_COMPUTE_WRITE        UINT8_C(0x02)
#define BGFX_BUFFER_DRAW_INDIRECT        UINT8_C(0x04)
#define BGFX_BUFFER_ALLOW_RESIZE         UINT8_C(0x08)
#define BGFX_BUFFER_INDEX32              UINT8_C(0x10)
#define BGFX_BUFFER_COMPUTE_READ_WRITE   (BGFX_BUFFER_COMPUTE_READ | BGFX_BUFFER_COMPUTE_WRITE)

///
#define BGFX_TEXTURE_NONE                UINT32_C(0x00000000)
#define BGFX_TEXTURE_U_MIRROR            UINT32_C(0x00000001)
#define BGFX_TEXTURE_U_CLAMP             UINT32_C(0x00000002)
#define BGFX_TEXTURE_U_SHIFT             0
#define BGFX_TEXTURE_U_MASK              UINT32_C(0x00000003)
#define BGFX_TEXTURE_V_MIRROR            UINT32_C(0x00000004)
#define BGFX_TEXTURE_V_CLAMP             UINT32_C(0x00000008)
#define BGFX_TEXTURE_V_SHIFT             2
#define BGFX_TEXTURE_V_MASK              UINT32_C(0x0000000c)
#define BGFX_TEXTURE_W_MIRROR            UINT32_C(0x00000010)
#define BGFX_TEXTURE_W_CLAMP             UINT32_C(0x00000020)
#define BGFX_TEXTURE_W_SHIFT             4
#define BGFX_TEXTURE_W_MASK              UINT32_C(0x00000030)
#define BGFX_TEXTURE_MIN_POINT           UINT32_C(0x00000040)
#define BGFX_TEXTURE_MIN_ANISOTROPIC     UINT32_C(0x00000080)
#define BGFX_TEXTURE_MIN_SHIFT           6
#define BGFX_TEXTURE_MIN_MASK            UINT32_C(0x000000c0)
#define BGFX_TEXTURE_MAG_POINT           UINT32_C(0x00000100)
#define BGFX_TEXTURE_MAG_ANISOTROPIC     UINT32_C(0x00000200)
#define BGFX_TEXTURE_MAG_SHIFT           8
#define BGFX_TEXTURE_MAG_MASK            UINT32_C(0x00000300)
#define BGFX_TEXTURE_MIP_POINT           UINT32_C(0x00000400)
#define BGFX_TEXTURE_MIP_SHIFT           10
#define BGFX_TEXTURE_MIP_MASK            UINT32_C(0x00000400)
#define BGFX_TEXTURE_RT                  UINT32_C(0x00001000)
#define BGFX_TEXTURE_RT_MSAA_X2          UINT32_C(0x00002000)
#define BGFX_TEXTURE_RT_MSAA_X4          UINT32_C(0x00003000)
#define BGFX_TEXTURE_RT_MSAA_X8          UINT32_C(0x00004000)
#define BGFX_TEXTURE_RT_MSAA_X16         UINT32_C(0x00005000)
#define BGFX_TEXTURE_RT_MSAA_SHIFT       12
#define BGFX_TEXTURE_RT_MSAA_MASK        UINT32_C(0x00007000)
#define BGFX_TEXTURE_RT_BUFFER_ONLY      UINT32_C(0x00008000)
#define BGFX_TEXTURE_RT_MASK             UINT32_C(0x0000f000)
#define BGFX_TEXTURE_COMPARE_LESS        UINT32_C(0x00010000)
#define BGFX_TEXTURE_COMPARE_LEQUAL      UINT32_C(0x00020000)
#define BGFX_TEXTURE_COMPARE_EQUAL       UINT32_C(0x00030000)
#define BGFX_TEXTURE_COMPARE_GEQUAL      UINT32_C(0x00040000)
#define BGFX_TEXTURE_COMPARE_GREATER     UINT32_C(0x00050000)
#define BGFX_TEXTURE_COMPARE_NOTEQUAL    UINT32_C(0x00060000)
#define BGFX_TEXTURE_COMPARE_NEVER       UINT32_C(0x00070000)
#define BGFX_TEXTURE_COMPARE_ALWAYS      UINT32_C(0x00080000)
#define BGFX_TEXTURE_COMPARE_SHIFT       16
#define BGFX_TEXTURE_COMPARE_MASK        UINT32_C(0x000f0000)
#define BGFX_TEXTURE_COMPUTE_WRITE       UINT32_C(0x00100000)
#define BGFX_TEXTURE_SRGB                UINT32_C(0x00200000)
#define BGFX_TEXTURE_RESERVED_SHIFT      24
#define BGFX_TEXTURE_RESERVED_MASK       UINT32_C(0xff000000)

#define BGFX_TEXTURE_SAMPLER_BITS_MASK (0 \
			| BGFX_TEXTURE_U_MASK \
			| BGFX_TEXTURE_V_MASK \
			| BGFX_TEXTURE_W_MASK \
			| BGFX_TEXTURE_MIN_MASK \
			| BGFX_TEXTURE_MAG_MASK \
			| BGFX_TEXTURE_MIP_MASK \
			| BGFX_TEXTURE_COMPARE_MASK \
			)

///
#define BGFX_RESET_NONE                  UINT32_C(0x00000000)
#define BGFX_RESET_FULLSCREEN            UINT32_C(0x00000001)
#define BGFX_RESET_FULLSCREEN_SHIFT      0
#define BGFX_RESET_FULLSCREEN_MASK       UINT32_C(0x00000001)
#define BGFX_RESET_MSAA_X2               UINT32_C(0x00000010)
#define BGFX_RESET_MSAA_X4               UINT32_C(0x00000020)
#define BGFX_RESET_MSAA_X8               UINT32_C(0x00000030)
#define BGFX_RESET_MSAA_X16              UINT32_C(0x00000040)
#define BGFX_RESET_MSAA_SHIFT            4
#define BGFX_RESET_MSAA_MASK             UINT32_C(0x00000070)
#define BGFX_RESET_VSYNC                 UINT32_C(0x00000080)
#define BGFX_RESET_MAXANISOTROPY         UINT32_C(0x00000100)
#define BGFX_RESET_CAPTURE               UINT32_C(0x00000200)
#define BGFX_RESET_HMD                   UINT32_C(0x00000400)
#define BGFX_RESET_HMD_DEBUG             UINT32_C(0x00000800)
#define BGFX_RESET_HMD_RECENTER          UINT32_C(0x00001000)
#define BGFX_RESET_FLIP_AFTER_RENDER     UINT32_C(0x00002000)
#define BGFX_RESET_SRGB_BACKBUFFER       UINT32_C(0x00004000)

///
#define BGFX_CAPS_TEXTURE_COMPARE_LEQUAL UINT64_C(0x0000000000000001)
#define BGFX_CAPS_TEXTURE_COMPARE_ALL    UINT64_C(0x0000000000000003)
#define BGFX_CAPS_TEXTURE_3D             UINT64_C(0x0000000000000004)
#define BGFX_CAPS_VERTEX_ATTRIB_HALF     UINT64_C(0x0000000000000008)
#define BGFX_CAPS_INSTANCING             UINT64_C(0x0000000000000010)
#define BGFX_CAPS_RENDERER_MULTITHREADED UINT64_C(0x0000000000000020)
#define BGFX_CAPS_FRAGMENT_DEPTH         UINT64_C(0x0000000000000040)
#define BGFX_CAPS_BLEND_INDEPENDENT      UINT64_C(0x0000000000000080)
#define BGFX_CAPS_COMPUTE                UINT64_C(0x0000000000000100)
#define BGFX_CAPS_FRAGMENT_ORDERING      UINT64_C(0x0000000000000200)
#define BGFX_CAPS_SWAP_CHAIN             UINT64_C(0x0000000000000400)
#define BGFX_CAPS_HMD                    UINT64_C(0x0000000000000800)
#define BGFX_CAPS_INDEX32                UINT64_C(0x0000000000001000)
#define BGFX_CAPS_DRAW_INDIRECT          UINT64_C(0x0000000000002000)

///
#define BGFX_CAPS_FORMAT_TEXTURE_NONE       UINT8_C(0x00)
#define BGFX_CAPS_FORMAT_TEXTURE_COLOR      UINT8_C(0x01)
#define BGFX_CAPS_FORMAT_TEXTURE_COLOR_SRGB UINT8_C(0x02)
#define BGFX_CAPS_FORMAT_TEXTURE_EMULATED   UINT8_C(0x04)
#define BGFX_CAPS_FORMAT_TEXTURE_VERTEX     UINT8_C(0x08)
#define BGFX_CAPS_FORMAT_TEXTURE_IMAGE      UINT8_C(0x10)

///
#define BGFX_VIEW_NONE   UINT8_C(0x00)
#define BGFX_VIEW_STEREO UINT8_C(0x01)

///
#define BGFX_SUBMIT_EYE_LEFT  UINT8_C(0x01)
#define BGFX_SUBMIT_EYE_RIGHT UINT8_C(0x02)
#define BGFX_SUBMIT_EYE_MASK  UINT8_C(0x03)
#define BGFX_SUBMIT_EYE_FIRST BGFX_SUBMIT_EYE_LEFT

///
#define BGFX_PCI_ID_NONE                UINT16_C(0x0000)
#define BGFX_PCI_ID_SOFTWARE_RASTERIZER UINT16_C(0x0001)
#define BGFX_PCI_ID_AMD                 UINT16_C(0x1002)
#define BGFX_PCI_ID_INTEL               UINT16_C(0x8086)
#define BGFX_PCI_ID_NVIDIA              UINT16_C(0x10de)

#endif // BGFX_DEFINES_H_HEADER_GUARD

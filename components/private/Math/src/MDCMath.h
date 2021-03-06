/*
 Copyright 2015-present the Material Components for iOS authors. All Rights Reserved.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

static inline CGFloat MDCCeil(CGFloat value) {
#if CGFLOAT_IS_DOUBLE
  return ceil(value);
#else
  return ceilf(value);
#endif
}

static inline CGFloat MDCFabs(CGFloat value) {
#if CGFLOAT_IS_DOUBLE
  return fabs(value);
#else
  return fabsf(value);
#endif
}

static inline CGFloat MDCDegreesToRadians(CGFloat degrees) {
#if CGFLOAT_IS_DOUBLE
  return degrees * (CGFloat)M_PI / 180.0;
#else
  return degrees * (CGFloat)M_PI / 180.f;
#endif
}

static inline bool MDCCGFloatEqual(CGFloat a, CGFloat b) {
  const CGFloat constantK = 3;
#if CGFLOAT_IS_DOUBLE
  const CGFloat epsilon = DBL_EPSILON;
  const CGFloat min = DBL_MIN;
#else
  const CGFloat epsilon = FLT_EPSILON;
  const CGFloat min = FLT_MIN;
#endif
  return (MDCFabs(a - b) < constantK * epsilon * MDCFabs(a + b) || MDCFabs(a - b) < min);
}

static inline CGFloat MDCFloor(CGFloat value) {
#if CGFLOAT_IS_DOUBLE
  return floor(value);
#else
  return floorf(value);
#endif
}

static inline CGFloat MDCHypot(CGFloat x, CGFloat y) {
#if CGFLOAT_IS_DOUBLE
  return hypot(x, y);
#else
  return hypotf(x, y);
#endif
}

// Checks whether the provided floating point number is exactly zero.
static inline BOOL MDCCGFloatIsExactlyZero(CGFloat value) {
  return (value == 0.f);
}

static inline CGFloat MDCPow(CGFloat value, CGFloat power) {
#if CGFLOAT_IS_DOUBLE
  return pow(value, power);
#else
  return powf(value, power);
#endif
}

static inline CGFloat MDCRint(CGFloat value) {
#if CGFLOAT_IS_DOUBLE
  return rint(value);
#else
  return rintf(value);
#endif
}

static inline CGFloat MDCRound(CGFloat value) {
#if CGFLOAT_IS_DOUBLE
  return round(value);
#else
  return roundf(value);
#endif
}

static inline CGFloat MDCSqrt(CGFloat value) {
#if CGFLOAT_IS_DOUBLE
  return sqrt(value);
#else
  return sqrtf(value);
#endif
}

/**
 Expand `rect' to the smallest standardized rect containing it with pixel-aligned origin and size.
 If @c scale is zero, then a scale of 1 will be used instead.

 @param rect the rectangle to align.
 @param scale the scale factor to use for pixel alignment.

 @return the input rectangle aligned to the nearest pixels using the provided scale factor.

 @see CGRectIntegral
 */
static inline CGRect MDCRectAlignToScale(CGRect rect, CGFloat scale) {
  if (CGRectIsNull(rect)) {
    return CGRectNull;
  }
  if (MDCCGFloatEqual(scale, 0)) {
    scale = 1;
  }

  if (MDCCGFloatEqual(scale, 1)) {
    return CGRectIntegral(rect);
  }

  CGPoint originalMinimumPoint = CGPointMake(CGRectGetMinX(rect), CGRectGetMinY(rect));
  CGPoint newOrigin = CGPointMake(MDCFloor(originalMinimumPoint.x * scale) / scale,
                                  MDCFloor(originalMinimumPoint.y * scale) / scale);
  CGSize adjustWidthHeight =
      CGSizeMake(originalMinimumPoint.x - newOrigin.x, originalMinimumPoint.y - newOrigin.y);
  return CGRectMake(newOrigin.x, newOrigin.y,
                    MDCCeil((CGRectGetWidth(rect) + adjustWidthHeight.width) * scale) / scale,
                    MDCCeil((CGRectGetHeight(rect) + adjustWidthHeight.height) * scale) / scale);
}

static inline CGPoint MDCPointRoundWithScale(CGPoint point, CGFloat scale) {
  if (MDCCGFloatEqual(scale, 0)) {
    return CGPointZero;
  }

  return CGPointMake(MDCRound(point.x * scale) / scale, MDCRound(point.y * scale) / scale);
}

/**
 Align the centerPoint of a view so that its origin is pixel-aligned to the nearest pixel.
 Returns @c CGRectZero if @c scale is zero or @c bounds is @c CGRectNull.

 @param center the unaligned center of the view.
 @param bounds the bounds of the view.
 @param scale the native scaling factor for pixel alignment.

 @return the center point of the view such that its origin will be pixel-aligned.
 */
static inline CGPoint MDCRoundCenterWithBoundsAndScale(CGPoint center,
                                                       CGRect bounds,
                                                       CGFloat scale) {
  if (MDCCGFloatEqual(scale, 0) || CGRectIsNull(bounds)) {
    return CGPointZero;
  }

  CGFloat halfWidth = CGRectGetWidth(bounds) / 2;
  CGFloat halfHeight = CGRectGetHeight(bounds) / 2;
  CGPoint origin = CGPointMake(center.x - halfWidth, center.y - halfHeight);
  origin = MDCPointRoundWithScale(origin, scale);
  return CGPointMake(origin.x + halfWidth, origin.y + halfHeight);
}

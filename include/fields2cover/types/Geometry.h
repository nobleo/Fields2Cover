//=============================================================================
//    Copyright (C) 2021-2022 Wageningen University - All Rights Reserved
//                     Author: Gonzalo Mier
//                           BSD-3 License
//=============================================================================

#pragma once
#ifndef FIELDS2COVER_TYPES_GEOMETRY_H_
#define FIELDS2COVER_TYPES_GEOMETRY_H_

#include <gdal/ogr_geometry.h>
#include <gdal/ogr_core.h>
#include <functional>
#include <memory>
#include <vector>
#include <string>
#include <boost/math/constants/constants.hpp>

namespace f2c::types {

class EmptyDestructor {};

template <class T, OGRwkbGeometryType R>
struct Geometry {
 public:
  Geometry();
  explicit Geometry(const T& g);
  explicit Geometry(std::shared_ptr<T> g);
  explicit Geometry(T* g, EmptyDestructor);
  explicit Geometry(const T* g);
  ~Geometry();
  explicit Geometry(const Geometry& g);
  Geometry(Geometry&& g);
  Geometry& operator=(Geometry&& g);
  Geometry& operator=(const Geometry& g);

  std::shared_ptr<T> operator->();
  std::shared_ptr<T> operator->() const;
  T* get() const;

  bool operator !=(const Geometry<T, R>& geom2) const;
  bool operator ==(const Geometry<T, R>& geom2) const;

  /// Get the minimum x value of the geometry.
  double getDimMinX() const;

  /// Get the maximum x value of the geometry.
  double getDimMaxX() const;

  /// Get the minimum y value of the geometry.
  double getDimMinY() const;

  /// Get the maximum y value of the geometry.
  double getDimMaxY() const;

  /// Get the height of the geometry
  double getHeight() const;

  /// Get the width of the geometry
  double getWidth() const;

  /// Get the manhattan distance of the diagonal of the rectangle that cover
  /// the geometry. A circle from any point of the geometry and with this
  /// distance as radius can be created and it will, at least, crosses the
  /// geometry.
  double getMinSafeLength() const;

  /// Compute shortest distance between this and another geometry.
  template <class T2, OGRwkbGeometryType R2>
  double Distance(const Geometry<T2, R2>& p) const;

  /// Check if this and another geometry are disjoint.
  template <class T2, OGRwkbGeometryType R2>
  bool Disjoint(const Geometry<T2, R2>& geom) const;

  /// Check if this and another geometry cross.
  template <class T2, OGRwkbGeometryType R2>
  bool Crosses(const Geometry<T2, R2>& geom) const;

  /// Check if this and another geometry touch each other.
  template <class T2, OGRwkbGeometryType R2>
  bool Touches(const Geometry<T2, R2>& geom) const;

  /// Check if this geometry is inside another geometry.
  template <class T2, OGRwkbGeometryType R2>
  bool Within(const Geometry<T2, R2>& geom) const;

  /// Check if this and another geometry intersects.
  template <class T2, OGRwkbGeometryType R2>
  bool Intersects(const Geometry<T2, R2>& geom) const;

  /// Transform from \f$ [-\inf, \inf) \f$ to \f$ [0, 2\pi) \f$ applying
  /// \f$2\pi\f$ modulus.
  /// @return value modulus in the range of \f$ [0, 2\pi) \f$
  static double mod_2pi(double val);

  static double getAngContinuity(double prev_val, double val);
  static std::vector<double> getAngContinuity(const std::vector<double>& val);

  /// Compute the smallest difference between two angles
  /// @param a first angle
  /// @param b second angle
  /// @return difference between both angles
  static double getAngleDiffAbs(double a, double b);

  bool isEmpty() const;

  std::string exportToWkt() const;
  void importFromWkt(const std::string& text);
  std::string exportToGML() const;
  std::string exportToKML() const;
  std::string exportToJson() const;

 protected:
  std::shared_ptr<T> data;
};

}  // namespace f2c::types

#include "fields2cover/types/Geometry_impl.hpp"

#endif  // FIELDS2COVER_TYPES_GEOMETRY_H_

// Copyright (C) 2017  I. Bogoslavskyi, C. Stachniss, University of Bonn

// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.

// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.

// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef PROJECTION_PROJECTION_PARAMS_H_
#define PROJECTION_PROJECTION_PARAMS_H_

#include <memory>
#include <string>
#include <vector>
#include <boost/thread.hpp>
#include "../utils/mem_util.h"
#include "../utils/radians.h"

namespace kamaz {

namespace hagen{

class SpanParams {
 public:
  /**
   * Enum for the direction of the span.
   */
  enum class Direction { HORIZONTAL, VERTICAL };

  SpanParams() {}
  SpanParams(const Radians& start_angle, const Radians& end_angle,
             const Radians& step) {
    _start_angle = start_angle;
    _end_angle = end_angle;
    _step = step;
    _num_beams = floor((_end_angle - _start_angle) / _step);
    _span = Radians::Abs(end_angle - start_angle);
  }

  SpanParams(const Radians& start_angle, const Radians& end_angle,
             int num_beams) {
    _start_angle = start_angle;
    _end_angle = end_angle;
    _num_beams = num_beams;
    _step = (_end_angle - _start_angle) / _num_beams;
    _span = Radians::Abs(end_angle - start_angle);
  }

  const Radians& start_angle() const { return _start_angle; }
  const Radians& end_angle() const { return _end_angle; }
  const Radians& step() const { return _step; }
  const Radians& span() const { return _span; }
  int num_beams() const { return _num_beams; }

  bool valid() const { return _num_beams > 0 && _span > 0_deg; }

 private:
  Radians _start_angle = 0_deg;
  Radians _end_angle = 0_deg;
  Radians _step = 0_deg;
  Radians _span = 0_deg;
  int _num_beams = 0;
};

/**
 * @brief      Class for projection parameters.
 */
class ProjectionParams {
 public:
  using Ptr = boost::shared_ptr<ProjectionParams>;
  using ConstPtr = const boost::shared_ptr<const ProjectionParams>;

  enum class Set { COLS, ROWS };
  ProjectionParams() {
  }
  ~ProjectionParams() {}

  /**
   * @brief      Set the angle span in a given direction.
   *
   * @param[in]  span_params  The span parameters packad into ::SpanParams.
   * @param[in]  direction    The direction. Must be one of
   *                          SpanParams::Direction.
   */
  void SetSpan(const SpanParams& span_params,
               const SpanParams::Direction& direction);

  /**
   * @brief      Set the angle spans in a given direction.
   *
   * @param[in]  span_params  The span parameters packad into ::SpanParams
   * @param[in]  direction    The direction. Must be one of
   *                          SpanParams::Direction.
   */
  void SetSpan(const std::vector<SpanParams>& span_params,
               const SpanParams::Direction& direction);

  inline const Radians& v_start_angle() const {
    return _v_span_params.start_angle();
  }
  inline const Radians& v_end_angle() const {
    return _v_span_params.end_angle();
  }
  inline const Radians& v_span() const { return _v_span_params.span(); }

  inline const Radians& h_start_angle() const {
    return _h_span_params.start_angle();
  }
  inline const Radians& h_end_angle() const {
    return _h_span_params.end_angle();
  }
  inline const Radians& h_span() const { return _h_span_params.span(); }
  inline size_t rows() const { return _row_angles.size(); }
  inline size_t cols() const { return _col_angles.size(); }
  inline size_t size() const { return rows() * cols(); }

  /**
   * @brief      Get angle from row
   *
   * @param[in]  row   The row
   *
   * @return     Angle in radians
   */
  const Radians AngleFromRow(int row) const;

  /**
   * @brief      Get angle from col
   *
   * @param[in]  col   The col
   *
   * @return     Angle in radians
   */
  const Radians AngleFromCol(int col) const;

  /**
   * @brief      Get row number from angle
   *
   * @param[in]  angle  The angle
   *
   * @return     Row number
   */
  size_t RowFromAngle(const Radians& angle) const;

  /**
   * @brief      Get col number from angle
   *
   * @param[in]  angle  The angle
   *
   * @return     Col number
   */
  size_t ColFromAngle(const Radians& angle) const;

  const std::vector<double>& RowAngleCosines() const;
  const std::vector<double>& ColAngleCosines() const;
  const std::vector<double>& RowAngleSines() const;
  const std::vector<double>& ColAngleSines() const;

  bool valid();

  double getMaxDistance();

  /**
   * @brief      Default parameters for 16 beam Velodyne
   *
   * @return     A pointer to parameters
   */
  static std::unique_ptr<ProjectionParams> VLP_16(double object_avoidance_zone);
  static std::unique_ptr<ProjectionParams> HDL_32(double object_avoidance_zone);
  static std::unique_ptr<ProjectionParams> HDL_64(double object_avoidance_zone);
  // static std::string LIDAR_V16;
  // std::string LIDAR_V32;
  // std::string LIDAR_V64;
  
 private:
  std::vector<Radians> FillVector(const SpanParams& span_params);
  std::vector<Radians> FillVector(const std::vector<SpanParams>& span_params);
  double object_avoidance_zone;
  static size_t FindClosest(const std::vector<Radians>& vec,
                            const Radians& val);

  void FillCosSin();

  SpanParams _v_span_params;
  SpanParams _h_span_params;

  std::vector<Radians> _col_angles;
  std::vector<Radians> _row_angles;

  std::vector<double> _col_angles_sines;
  std::vector<double> _col_angles_cosines;

  std::vector<double> _row_angles_sines;
  std::vector<double> _row_angles_cosines;
};

}  // namespace kamaz
}
#endif  // SRC_PROJECTIONS_PROJECTION_PARAMS_H_
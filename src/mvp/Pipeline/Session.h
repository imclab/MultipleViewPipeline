/// \file Session.h
///
/// Session class
///

#ifndef __MVP_PIPELINE_SESSION_H__
#define __MVP_PIPELINE_SESSION_H__

#include <mvp/Pipeline/JobDesc.pb.h>
#include <mvp/Pipeline/SessionDesc.pb.h>

#include <vw/Math/Vector.h>
#include <vw/Math/BBox.h>

// Rather than including an ENTIRE PlateGeoReference, we
// just hold onto its desc.
#include <vw/Plate/PlateGeoReferenceDesc.pb.h>

namespace mvp {
namespace image {

class OrbitalImageCatalog;

}} // namespace image,mvp

namespace mvp {
namespace pipeline {

class Session {
  SessionDesc m_session_desc;
  vw::platefile::PlateGeoReferenceDesc m_plate_georef_desc;
  boost::shared_ptr<image::OrbitalImageCatalog> m_catalog;
  vw::Vector2i m_cursor;
  vw::BBox2i m_render_bbox;

  public:
    Session() {}

    Session(SessionDesc const& session_desc) { reset(session_desc); }

    void reset(SessionDesc const& session_desc);

    JobDesc job(int col, int row, int level);

    JobDesc next_job();

    bool has_next_job() { return m_render_bbox.contains(m_cursor); }
    
    int size() { return m_render_bbox.width() * m_render_bbox.height(); }
};

}} // namespace pipeline, mvp

#endif

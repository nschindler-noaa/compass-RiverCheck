#ifndef SEGMENTVIEWS_H
#define SEGMENTVIEWS_H

#include <QtGui/QGraphicsItem>
#include <QPainter>
#include<QtGui/QStyleOptionGraphicsItem>

#include "RiverSegment.h"

class ReachTopViewItem : public QGraphicsItem
{
public:
    ReachTopViewItem(QGraphicsItem *parent);
    void setValues (float len, float upr_width, float low_width, float bd_width, float x);
    void setLength (float len) {length = len; endx = startx + length; update();}
    void setUpperWidth (float upr_width) {upper_width = upr_width; upper_wid_2 = upper_width / 2.0; update();}
    void setLowerWidth (float lwr_width) {lower_width = lwr_width; lower_wid_2 = lower_width / 2.0; update();}
    void setBedWidth (float bd_width) {bed_width = bd_width; bed_wid_2 = bed_width / 2.0; update();}
    void setStartX (float x) {startx = x; endx = startx + length; update();}
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

protected:
    float length;
    float upper_width;
    float upper_wid_2;
    float lower_width;
    float lower_wid_2;
    float bed_width;
    float bed_wid_2;
    float startx;
    float endx;
};

class ReachSideViewItem : public QGraphicsItem
{
public:
    ReachSideViewItem(QGraphicsItem *parent);
    void setValues (float len, float upr_elev, float low_elev, float upr_depth, float lwr_depth, float x);
    void setLength (float len) {length = len; endx = startx + length; update();}
    void setUpperElev (float upr_elev) {upper_elev = upr_elev; upper_top_elev = upper_elev + upper_depth; update();}
    void setLowerElev (float lwr_elev) {lower_elev = lwr_elev; lower_top_elev = lower_elev + lower_depth; update();}
    void setUpperDepth (float upr_depth) {upper_depth = upr_depth; upper_top_elev = upper_elev + upper_depth; update();}
    void setLowerDepth (float lwr_depth) {lower_depth = lwr_depth; lower_top_elev = lower_elev + lower_depth; update();}
    void setStartX (float x) {startx = x; endx = startx + length; update();}
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

protected:
    float length;
    float upper_elev;
    float upper_top_elev;
    float lower_elev;
    float lower_top_elev;
    float upper_depth;
    float lower_depth;
    float startx;
    float endx;
};

class ReachSectionItem : public QGraphicsItem
{
public:
    ReachSectionItem(QGraphicsItem *parent);
    void setValues (float wid, float dep, float bd_width, float elev);
    void setWidth (float wid) {width = wid; wid_2 = width / 2.0; update();}
    void setDepth (float dep) {depth = dep; top_elevation = elevation + depth; update();}
    void setBedWidth (float bd_width) {bed_width = bd_width; bed_wid_2 = bed_width / 2.0; update();}
    void setElevation (float elev) {elevation = elev; top_elevation = elevation + depth; update();}
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

protected:
    float width;
    float wid_2;
    float depth;
    float bed_width;
    float bed_wid_2;
    float elevation;
    float top_elevation;
};

class DamTopViewItem : public QGraphicsItem
{
public:
    DamTopViewItem(QGraphicsItem *parent);
    void setValues (float len, float wid, float b_len, float tr_len, int n_gates, float wd_gates, Location sd, float x);
    void setWidth (float wid) {width = wid; wid_2 = width / 2.0; update();}
    void setBasinLength (float len) {basin_length = len; tailrace_length = 2.0 * len; update();}
    void setTailraceLength (float len) {tailrace_length = len; update();}
    void setNumGates (int nm_gates) {num_spill_gates = nm_gates; update();}
    void setWidthGates (float wd_gates) {width_each_gate = wd_gates; update();}
    void setSpillSide (Location sd) {spill_side = sd; update();}
    void setStartX (float x) {startx = x; endx = startx + 20.0; update();}
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

protected:
    float length;
    float width;
    float wid_2;
    float basin_length;
    float tailrace_length;
    int num_spill_gates;
    float width_each_gate;
    Location spill_side;
    float startx;
    float endx;
};

class DamSideViewItem : public QGraphicsItem
{
public:
    DamSideViewItem(QGraphicsItem *parent);
    void setValues (float len, float fb_elev, float tr_elev, float b_len, float tr_len, float by_elev, float fl_elev, float x);
    void setForebayElev (float fb_elev) {forebay_elev = fb_elev; update();}
    void setTailraceElev (float tr_elev) {tailrace_elev = tr_elev; update();}
    void setBasinLength (float len) {basin_length = len; update();}
    void setByPassElev (float by_elev) {bypass_elev = by_elev; update();}
    void setFloorElev (float fl_elev) {floor_elev = fl_elev; update();}
    void setStartX (float x) {startx = x; endx = startx + 20.0; update();}
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

protected:
    float length;
    float forebay_elev;
    float forebay_depth;
    float tailrace_depth;
    float tailrace_elev;
    float tailrace_length;
    float basin_length;
    float bypass_elev;
    float floor_elev;
    float startx;
    float endx;
};

class DamSectionItem : public QGraphicsItem
{
public:
    DamSectionItem(QGraphicsItem *parent);
    void setValues (float wid, float dep, int n_gates, float w_gates, Location sd, float tr_elev, float by_elev, float elev);
    void setWidth (float wid) {width = wid; wid_2 = width / 2.0; update();}
    void setDepth (float dep) {depth = dep; top_elevation = elevation - depth; update();}
    void setNumGates (int nm_gates) {num_spill_gates = nm_gates; update();}
    void setWidthGates (float wd_gates) {width_each_gate = wd_gates; update();}
    void setSpillSide (Location sd) {spill_side = sd; update();}
    void setTailraceElev (float tr_elev) {tailrace_elev = -tr_elev; update();}
    void setByPassElev (float by_elev) {bypass_elev = -by_elev; update();}
    void setElevation (float elev) {elevation = -elev; top_elevation = elevation - depth; update();}
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

protected:
    float width;
    float wid_2;
    float depth;
    float tailrace_elev;
    int num_spill_gates;
    float width_each_gate;
    Location spill_side;
    float bypass_elev;
    float elevation;
    float top_elevation;
};


#endif // SEGMENTVIEWS_H

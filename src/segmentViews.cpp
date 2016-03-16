#include "segmentViews.h"

ReachTopViewItem::ReachTopViewItem(QGraphicsItem *parent) :
    QGraphicsItem (parent)
{
    length = 0.0;
    upper_width = 0.0;
    upper_wid_2 = 0.0;
    lower_width = 0.0;
    lower_wid_2 = 0.0;
    bed_width = 0.0;
    bed_wid_2 = 0.0;
    startx = 0.0;
}

void ReachTopViewItem::setValues(float len, float upr_width, float low_width, float bd_width, float x)
{
    length = len;
    upper_width = upr_width;
    upper_wid_2 = upr_width / 2.0;
    lower_width = low_width;
    lower_wid_2 = low_width / 2.0;
    bed_width = bd_width;
    bed_wid_2 = bd_width / 2.0;
    startx = x;
    endx = x + len;
    update ();
}

void ReachTopViewItem::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath path (QPointF(startx, -lower_wid_2));
    QPainterPath bed (QPointF(startx, -bed_wid_2));
    path.lineTo(endx, -upper_wid_2);
    path.lineTo(endx, upper_wid_2);
    path.lineTo(startx, lower_wid_2);
    path.lineTo(startx, -lower_wid_2);

    painter->setBrush(Qt::cyan);
    painter->setPen(QPen(Qt::blue, 2));
    painter->drawPath(path);
/*    painter->drawLine(startx, lower_wid_2, startx, -lower_wid_2);
    painter->drawLine (startx, -lower_wid_2, endx, -upper_wid_2);
    painter->drawLine(endx, -upper_wid_2, endx, upper_wid_2);
    painter->drawLine(endx, upper_wid_2, startx, lower_wid_2);*/

    bed.lineTo(endx, -bed_wid_2);
    bed.lineTo(endx, bed_wid_2);
    bed.lineTo(startx, bed_wid_2);
    bed.lineTo(startx, -bed_wid_2);
    painter->drawPath(bed);
//    painter->drawRect(startx, -bed_wid_2, length, bed_width);
}

QRectF ReachTopViewItem::boundingRect() const
{
    qreal lft = startx - 1.0;
    qreal top = -lower_wid_2 - 1.0;
    qreal wid = length + 2.0;
    qreal hgt = lower_width + 2.0;
    return QRectF (lft, top, wid, hgt);
//    return QRectF (startx - 1.0, -lower_wid_2 - 1.0, length + 2.0, lower_width + 2.0);
}


ReachSideViewItem::ReachSideViewItem(QGraphicsItem *parent) :
    QGraphicsItem (parent)
{
    length = 0.0;
    upper_elev = 0.0;
    lower_elev = 0.0;
    upper_depth = 0.0;
    lower_depth = 0.0;
    upper_top_elev = 0.0;
    lower_top_elev = 0.0;
    startx = 0.0;
    endx = 0.0;
}

void ReachSideViewItem::setValues(float len, float upr_elev, float lwr_elev, float upr_depth, float lwr_depth, float x)
{
    length = len;
    upper_elev = upr_elev;
    upper_top_elev = upr_elev + upr_depth;
    lower_elev = lwr_elev;
    lower_top_elev = lwr_elev + lwr_depth;
    upper_depth = upr_depth;
    lower_depth = lwr_depth;
    startx = x;
    endx = x + len;
    update ();
}

void ReachSideViewItem::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath path (QPointF(startx, -lower_top_elev));
    path.lineTo(startx, -lower_elev);
    path.lineTo(endx, -upper_elev);
    path.lineTo(endx, -upper_top_elev);
    path.lineTo(startx, -lower_top_elev);

    painter->setBrush(Qt::cyan);
    painter->setPen(QPen(Qt::blue, 2));
    painter->drawPath(path);
/*    painter->drawLine(startx, -lower_top_elev, startx, -lower_elev);
    painter->drawLine(startx, -lower_elev, endx, -upper_elev);
    painter->drawLine(endx, -upper_elev, endx, -upper_top_elev);
    painter->drawLine(endx, -upper_top_elev, startx, -lower_top_elev);*/
}

QRectF ReachSideViewItem::boundingRect() const
{
    qreal lft = startx - 1.0;
    qreal top = -upper_top_elev - 1.0;
    qreal wid = length + 2.0;
    qreal hgt = upper_top_elev - lower_elev + 2.0;
    return QRectF (lft, top, wid, hgt);
//    return QRectF (startx - 1.0, -lower_elev, length, (upper_top_elev - lower_elev));
}


ReachSectionItem::ReachSectionItem(QGraphicsItem *parent) :
    QGraphicsItem (parent)
{
    width = 0.0;
    depth = 0.0;
    bed_width = 0.0;
    elevation = 0.0;
}

void ReachSectionItem::setValues(float wid, float dep, float bd_width, float elev)
{
    width = wid;
    wid_2 = wid / 2.0;
    depth = dep;
    bed_width = bd_width;
    bed_wid_2 = bd_width / 2.0;
    elevation = elev;
    top_elevation = elev + dep;
    update ();
}

void ReachSectionItem::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath path (QPointF(-wid_2, -top_elevation));
    path.lineTo(wid_2, -top_elevation);
    path.lineTo(bed_wid_2, -elevation);
    path.lineTo(-bed_wid_2, -elevation);
    path.lineTo(-wid_2, -top_elevation);

    painter->setPen(QPen(Qt::blue, 2));
    painter->drawPath(path);
/*    painter->drawLine(-wid_2, -top_elevation, wid_2, -top_elevation);
    painter->drawLine(-wid_2, -top_elevation, -bed_wid_2, -elevation);
    painter->drawLine(-bed_wid_2, -elevation, bed_wid_2, -elevation);
    painter->drawLine(bed_wid_2, -elevation, wid_2, -top_elevation);*/

}

QRectF ReachSectionItem::boundingRect() const
{
    qreal lft = -wid_2 - 1.0;
    qreal top = -elevation - 1.0;
    qreal wid = width + 2.0;
    qreal hgt = depth + 2.0;
    return QRectF (lft, top, wid, hgt);
//    return QRectF (-wid_2, -elevation, width, depth);
}

DamTopViewItem::DamTopViewItem(QGraphicsItem *parent) :
    QGraphicsItem (parent)
{
    width = 0.0;
    num_spill_gates = 0;
    width_each_gate = 0.0;
    spill_side = Left;
    startx = 0.0;
}

void DamTopViewItem::setValues(float len, float wid, float b_len, float tr_len, int n_gates, float wd_gates, Location sd, float x)
{
    length = len;
    width = wid;
    wid_2 = wid / 2.0;
    basin_length = b_len;
    tailrace_length = tr_len;
    num_spill_gates = n_gates;
    width_each_gate = wd_gates;
    spill_side = sd;
    startx = x;
    endx = x + len;
    update ();
}

void DamTopViewItem::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    float starty = 0.0;
    float wid_spill = num_spill_gates * width_each_gate;

    painter->setPen (QPen(Qt::blue, 2));
    painter->setBrush(Qt::lightGray);

    // draw dam body
    painter->drawRect (startx, -wid_2, length, width);

    // draw tailrace
    painter->drawRect(startx - tailrace_length, -wid_2, tailrace_length, width);

    painter->setBrush (Qt::cyan);

    // draw spillway
    switch (spill_side)
    {
    case Left:
    {
        for (int i = 0; i < num_spill_gates; i++)
        {
            painter->drawRect(startx, starty, length, width_each_gate);
            starty += width_each_gate;
        }
        break;
    }
    case Right:
    {
        starty = -(width_each_gate * (float)num_spill_gates);
        for (int i = 0; i < num_spill_gates; i++)
        {
            painter->drawRect(startx, starty, length, width_each_gate);
            starty += width_each_gate;
        }
        break;
    }
    default:
        break;
    }

    // get start for basin

    if (starty > 1.0)
        starty = 0.0;
    else
        starty = -wid_spill;

    // draw basin
    if (basin_length > 0.0)
        painter->drawRect (startx - basin_length, starty, basin_length, wid_spill);

}

QRectF DamTopViewItem::boundingRect() const
{
    qreal lft = -tailrace_length - 1.0;
    qreal top = -wid_2 - 1.0;
    qreal wid = tailrace_length + length + 2.0;
    qreal hgt = width + 2.0;
    return QRectF (lft, top, wid, hgt);
//    return QRectF (-tailrace_length, -wid_2, (tailrace_length + length), width);
}

/*void DamTopViewItem::setSpillSide ()*/

DamSideViewItem::DamSideViewItem(QGraphicsItem *parent) :
    QGraphicsItem (parent)
{
    length = 0.0;
    forebay_elev = 0.0;
    forebay_depth = 0.0;
    tailrace_elev = 0.0;
    tailrace_depth = 0.0;
    tailrace_length = 0.0;
    basin_length = 0.0;
    bypass_elev = 0.0;
    floor_elev = 0.0;
    startx = 0.0;
    endx = 0.0;
}

void DamSideViewItem::setValues(float len, float fb_elev, float tr_elev, float b_len, float tr_len, float by_elev, float fl_elev, float x)
{
    length = len;
    forebay_elev = fb_elev;
    forebay_depth = fb_elev - fl_elev;
    tailrace_elev = tr_elev;
    tailrace_depth = tr_elev - fl_elev;
    tailrace_length = tr_len;
    basin_length = b_len;
    bypass_elev = by_elev;
    floor_elev = fl_elev;
    startx = x;
    endx = x + len;
    update ();
}

void DamSideViewItem::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath side, spill;
    float basin_floor_elev = (tailrace_elev + floor_elev) / 2.0;

    painter->setBrush(Qt::lightGray);
    painter->setPen(QPen(Qt::blue, 2));
    // draw dam body
    side.moveTo(startx, -floor_elev);
    side.lineTo(startx + length, -floor_elev);
    side.lineTo(startx + length, -forebay_elev);
    side.lineTo(startx + length / 2.0, -forebay_elev);
    side.lineTo(startx, -tailrace_elev);
    side.lineTo(startx, -floor_elev);

//    painter->drawRect(startx, -floor_elev, length, -(forebay_elev - floor_elev));

//    painter->drawRect(-tailrace_length, -floor_elev, tailrace_length, -tailrace_depth);

    // draw spill
/*    spill.moveTo(startx, -floor_elev);
    spill.lineTo(startx + length / 4.0, -floor_elev);
    spill.lineTo(startx + length / 4.0 * 3.0, -forebay_elev);
    spill.lineTo(startx + length / 2.0, -forebay_elev);
    spill.lineTo(startx, -floor_elev);*/

//        painter->drawRect(-basin_length, -floor_elev, basin_length, -tailrace_depth);
    // draw tailrace
    side.moveTo(startx - tailrace_length, -floor_elev);
    side.lineTo(startx, -floor_elev);
    side.lineTo(startx, -tailrace_elev);
    side.lineTo(startx - tailrace_length, -tailrace_elev);
    side.lineTo(startx - tailrace_length, -floor_elev);

    if (basin_length > 0.0)
    {
        // draw basin
        spill.moveTo(startx - basin_length, -basin_floor_elev);
        spill.lineTo(startx, -basin_floor_elev);
        spill.lineTo(startx, -tailrace_elev);
        spill.lineTo(startx - basin_length, -tailrace_elev);
        spill.lineTo(startx - basin_length, -basin_floor_elev);
    }

    // draw bypass
    if (bypass_elev > tailrace_elev)
    {
        float bypass_length = length / 4.0;
        float bypass_depth = (forebay_elev - bypass_elev) / 4.0;
        if (bypass_depth < 2.0) bypass_depth = 2.0;
//        painter->drawRect((startx + length - bypass_length), -bypass_elev, bypass_length, -(bypass_depth + 2.0));
        spill.moveTo(length - bypass_length, -bypass_elev);
        spill.lineTo(length, -bypass_elev);
        spill.lineTo(length, -(bypass_elev + bypass_depth));
        spill.lineTo(length - bypass_length, -(bypass_elev + bypass_depth));
        spill.lineTo(length - bypass_length, -bypass_elev);
    }
    painter->drawPath(side);

    painter->setBrush(Qt::cyan);
    painter->drawPath(spill);
}

QRectF DamSideViewItem::boundingRect() const
{
    qreal lft = -tailrace_length - 1.0;
    qreal top = -floor_elev + 1.0;
    qreal wid = tailrace_length + length + 2.0;
    qreal hgt = -forebay_depth - 2.0;
    return QRectF (lft, top, wid, hgt);
//    return QRectF (-(tailrace_length + 2), -(floor_elev + 2), (tailrace_length + length + 4), -(forebay_depth + 4));
}


DamSectionItem::DamSectionItem(QGraphicsItem *parent) :
    QGraphicsItem (parent)
{
    width = 0.0;
    wid_2 = 0.0;
    depth = 0.0;
    tailrace_elev = 0.0;
    num_spill_gates = 0;
    width_each_gate = 0.0;
    spill_side = Left;
    bypass_elev = 0.0;
    elevation = 0.0;
    top_elevation = 0.0;
}

void DamSectionItem::setValues(float wid, float dep, int n_gates, float w_gates, Location sd, float tr_elev, float by_elev, float elev)
{
    width = wid;
    wid_2 = wid / 2.0;
    depth = dep;
    tailrace_elev = tr_elev;
    num_spill_gates = n_gates;
    width_each_gate = w_gates;
    spill_side = sd;
    bypass_elev = by_elev;
    elevation = elev;
    top_elevation = elev + dep;
    update ();
}

void DamSectionItem::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath sec, spill;
    float startx = -wid_2;
    float basin_floor_elev = (tailrace_elev + elevation) / 2.0;
    float spill_width = (float)num_spill_gates * width_each_gate;

    // draw dam body
    sec.moveTo(startx, -elevation);
    sec.lineTo(wid_2, -elevation);
    sec.lineTo(wid_2, -top_elevation);
    sec.lineTo(startx, -top_elevation);
    sec.lineTo(startx, -elevation);
//    painter->drawRect(startx, -elevation, width, -depth);

    // draw tailrace
/*    sec.moveTo(-wid_2, elevation);
    sec.lineTo(wid_2, elevation);
    sec.lineTo(wid_2, tailrace_elev);
    sec.lineTo(-wid_2, tailrace_elev);
    sec.lineTo(-wid_2, elevation);*/
//    painter->drawRect(startx, -elevation, width, -tailrace_depth);

    painter->setPen(QPen(Qt::blue, 2)); // set edge color
    painter->setBrush(Qt::lightGray);   // set fill color for structure
    painter->drawPath(sec);
    // draw tailrace
    painter->drawLine(startx, -tailrace_elev, wid_2, -tailrace_elev);

    // draw spillway
    switch (spill_side)
    {
    case Left:
    {
        startx = 0.0;
        break;
    }
    case Right:
    {
        startx = -(spill_width);
        break;
    }
    default:
        break;
    }
    for (int i = 0; i < num_spill_gates; i++)
    {
        float start = startx + i * width_each_gate;
        float end = start + width_each_gate - 2.0;
        spill.moveTo(start, -tailrace_elev);
        spill.lineTo(end, -tailrace_elev);
        spill.lineTo(end, -top_elevation + 2.0);
        spill.lineTo(start, -top_elevation + 2.0);
        spill.lineTo(start, -tailrace_elev);
//        painter->drawRect(startx, -elevation, width_each_gate - 2.0, -depth);
//        startx += width_each_gate;
    }

        // draw basin
        spill.moveTo(startx, -basin_floor_elev);
        spill.lineTo(startx + spill_width, -basin_floor_elev);
        spill.lineTo(startx + spill_width, -tailrace_elev);
        spill.lineTo(startx, -tailrace_elev);
        spill.lineTo(startx, -basin_floor_elev);
//        painter->drawRect(-wid_2, -elevation, wid_2, -tailrace_depth);
        // draw bypass
/*        if (bypass_elev > 0.0)
        {
            float bypass_depth = elevation + depth - bypass_elev;
//            if (bypass_depth > 5.0)
                bypass_depth = -5.0;
            spill.moveTo(-wid_2, bypass_elev);
            spill.lineTo(0.0, bypass_elev);
            spill.lineTo(0.0, bypass_elev + bypass_depth);
            spill.lineTo(-wid_2, bypass_elev + bypass_depth);
            spill.lineTo(-wid_2, bypass_elev);
//            painter->drawRect(-wid_2, -bypass_elev, wid_2, -(bypass_depth - 2.0));
        }
    }
    else
    {
        // draw basin
        spill.moveTo(0.0, -basin_floor_elev);
        spill.lineTo(wid_2, -basin_floor_elev);
        spill.lineTo(wid_2, -tailrace_elev);
        spill.lineTo(0.0, -tailrace_elev);
        spill.lineTo(0.0, -basin_floor_elev);*/
//        painter->drawRect(0.0, -elevation, wid_2, -tailrace_depth);
        // draw bypass
/*        if (bypass_elev > 0.0)
        {
            float bypass_depth = elevation + depth - bypass_elev;
//            if (bypass_depth > 5.0)
                bypass_depth = -5.0;
            spill.moveTo(0.0, bypass_elev);
            spill.lineTo(wid_2, bypass_elev);
            spill.lineTo(wid_2, bypass_elev + bypass_depth);
            spill.lineTo(0.0, bypass_elev + bypass_depth);
            spill.lineTo(0.0, bypass_elev);
//            painter->drawRect(0.0, -bypass_elev, wid_2, -(bypass_depth - 2.0));
        }
    }*/
    painter->setBrush(Qt::cyan);  // set fill color for water
    painter->drawPath(spill);
}

QRectF DamSectionItem::boundingRect() const
{
    qreal lft = -wid_2 - 1.0;
    qreal top = -elevation + 1.0;
    qreal wid = width + 2.0;
    qreal hgt = -depth - 2.0;
    return QRectF (lft, top, wid, hgt);
//    return QRectF (-wid_2, -elevation, width, -depth);
}

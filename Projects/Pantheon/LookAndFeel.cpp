#include "LookAndFeel.h"

PanLook::PanLook() : PanLook(Type::Pan)
{
}

PanLook::PanLook(Type t) : type(t)
{
}

void PanLook::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider) {
    const auto outline = slider.findColour (Slider::rotarySliderOutlineColourId);

    Colour fill;
    float fillOriginAngle;

    if (type == Type::Pan) {
        fill = sliderPos > 0.5f ? rightColour : leftColour;
        fillOriginAngle = MathConstants<float>::twoPi;
    } else {
        fill = rightColour;
        fillOriginAngle = rotaryStartAngle;
    }

    const auto bounds = Rectangle<int> (x, y, width, height).toFloat().reduced (10);

    const auto radius = jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
    const auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    const auto lineW = jmin (8.0f, radius * 0.25f);
    const auto arcRadius = radius - lineW * 0.5f;

    Path backgroundArc;
    backgroundArc.addCentredArc (bounds.getCentreX(),
                                 bounds.getCentreY(),
                                 arcRadius,
                                 arcRadius,
                                 0.0f,
                                 rotaryStartAngle,
                                 rotaryEndAngle,
                                 true);

    g.setColour (outline);
    g.strokePath (backgroundArc, PathStrokeType (lineW, PathStrokeType::mitered, PathStrokeType::butt));

    if (slider.isEnabled())
    {
        Path valueArc;
        valueArc.addCentredArc (bounds.getCentreX(),
                                bounds.getCentreY(),
                                arcRadius,
                                arcRadius,
                                0.0f,
                                fillOriginAngle,
                                toAngle,
                                true);

        g.setColour (fill);
        g.strokePath (valueArc, PathStrokeType (lineW, PathStrokeType::mitered, PathStrokeType::butt));
    }

    Path thumbArc;

    const auto thumbArcStartAngle = toAngle - 0.1f;
    const auto thumbArcEndAngle = toAngle + 0.1f;
    
    thumbArc.addCentredArc(bounds.getCentreX(),
                           bounds.getCentreY(),
                           arcRadius - lineW * 1.5f,
                           arcRadius - lineW * 1.5f,
                           0.f,
                           thumbArcStartAngle,
                           thumbArcEndAngle,
                           true);

    g.setColour(thumbColour);
    g.strokePath(thumbArc, PathStrokeType(4.f * lineW, PathStrokeType::mitered, PathStrokeType::butt));
}
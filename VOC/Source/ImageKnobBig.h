#pragma once
#include "JuceHeader.h"
#include "BinaryData.h"

class ImageKnobBig : public juce::Slider
{
public:
    ImageKnobBig()
    {
        auto imageData = BinaryData::knobBig_png;  // Replace with the actual file name
        auto imageSize = BinaryData::knobBig_pngSize;  // Replace with the actual file name

        juce::Image originalImage = juce::ImageFileFormat::loadFrom(imageData, (size_t)imageSize);

        // Resize the image based on the component
        auto maxDimension = 100;  // Use a dimension that fits your component well
        knobImage = originalImage.rescaled(maxDimension, maxDimension, juce::Graphics::highResamplingQuality);

        setSliderStyle(RotaryVerticalDrag);  // Set the appropriate Slider style
        setTextBoxStyle(NoTextBox, false, 0, 0);  // Hide the textbox, if present
    }

    void paint(juce::Graphics& g) override
    {
        auto bounds = getLocalBounds();
        auto centre = bounds.getCentre();

        // Calculate the rotation angle in radians
        auto angle = getRadians();

        // Prepare a transformation that rotates the image around its center
        juce::AffineTransform transform = juce::AffineTransform::rotation(angle, knobImage.getWidth() / 2.0, knobImage.getHeight() / 2.0)
            .translated(centre.getX() - knobImage.getWidth() / 2.0, centre.getY() - knobImage.getHeight() / 2.0);

        // Draw the transformed image
        g.drawImageTransformed(knobImage, transform);
    }

    double getRadians() const
    {
        // Define the start and end angle in radians (e.g., -135 to 135 degrees)
        const double startAngle = -juce::MathConstants<double>::pi * 3.0 / 4.0;  // -135 degrees
        const double endAngle = juce::MathConstants<double>::pi * 3.0 / 4.0;  // 135 degrees

        // Map the slider value to radians
        auto proportion = (getValue() - getMinimum()) / (getMaximum() - getMinimum());
        return startAngle + proportion * (endAngle - startAngle);
    }

private:
    juce::Image knobImage;
};

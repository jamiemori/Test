/*
  ==============================================================================

    MinimalLook.h
    Created: 20 Jan 2015 8:34:46am
    Author:  Yoda

  ==============================================================================
*/

#ifndef MINIMALLOOK_H_INCLUDED
#define MINIMALLOOK_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "math.h"

class MinimalLook : public LookAndFeel_V2 
{
public:
	void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override
	{
		    const float radius = width/2 - 2.0f;
		    const float centreX = x + width * 0.5f;
		    const float centreY = y + height * 0.5f;
		    const float rx = centreX - radius;
		    const float ry = centreY - radius;
		    const float rw = radius * 2.0f;
		    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
		    const float arcThick = 2.0f;
			const float redArcRadius = radius - 7*arcThick;

			const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

			Rectangle<float> r (rx, ry, rw, rw);
			Rectangle<float> r2 (rx, ry, rw/40, rw/7);

			const float needleRad = r2.getWidth()/(r.getWidth()/2);
			Path needle;
			needle.addRectangle (r2.withPosition (Point<float> (r.getCentreX() - (r2.getWidth() / 2.0f), r.getY())));

			Path redArcs;
			redArcs.addCentredArc(centreX, centreY, redArcRadius, redArcRadius, angle, 2*float_Pi/8, 2*float_Pi * 3/8, true);
			redArcs.addCentredArc(centreX, centreY, redArcRadius, redArcRadius, angle, 2*float_Pi*5/8, 2*float_Pi * 7/8, true);

		    Path arcs;	
		    arcs.addCentredArc(centreX, centreY, radius, radius, angle, needleRad, 2*float_Pi- needleRad, true);
		    arcs.addCentredArc(centreX, centreY, radius- 3*arcThick , radius- 3*arcThick, angle, needleRad, 2*float_Pi- needleRad, true);


			if (isMouseOver != true)
			{
				g.setColour(Colour (0xfffc5332)); 
				g.fillPath (needle, AffineTransform::rotation (angle, r.getCentreX(), r.getCentreY())); 
				g.strokePath (redArcs, PathStrokeType (arcThick));
				g.strokePath (redArcs, PathStrokeType (arcThick));
				
			    g.setColour (Colour (0xff93bfd2));  
		       	g.strokePath (arcs, PathStrokeType (arcThick));
				g.strokePath (arcs, PathStrokeType (arcThick/2));	
			}

			else
			{
				g.setColour(Colour (0xfffc5332).withAlpha(0.5f)); 
				g.fillPath (needle, AffineTransform::rotation (angle, r.getCentreX(), r.getCentreY())); 
				g.strokePath (redArcs, PathStrokeType (arcThick));
				g.strokePath (redArcs, PathStrokeType (arcThick));
				
			    g.setColour (Colour (0xff93bfd2).withAlpha(0.5f));  
		       	g.strokePath (arcs, PathStrokeType (arcThick));
				g.strokePath (arcs, PathStrokeType (arcThick/2));	
			}
		   	
	}

};

#endif  // MINIMALLOOK_H_INCLUDED

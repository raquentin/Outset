class OscTab : public juce::Component, private juce::Slider::Listener
{
public:
    OscTab(const juce::String& title)
        : tabTitle(title)
    {
        initializeSlider(oscLevelSlider, oscLevelLabel, "Level", juce::Slider::SliderStyle::LinearHorizontal, 0.0, 1.0, 0.01, 0.5);
        initializeSlider(oscFineTuneSlider, oscFineTuneLabel, "Fine Tune", juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, -50.0, 50.0, 0.01, 0.0);
        initializeSlider(oscCoarseTuneSlider, oscCoarseTuneLabel, "Coarse Tune", juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, -12.0, 12.0, 1.0, 0.0);
        initializeSlider(oscRatioSlider, oscRatioLabel, "Ratio", juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.01, 4.0, 0.01, 1.0);
        initializeSlider(oscFeedbackSlider, oscFeedbackLabel, "Feedback", juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0, 100.0, 1.0, 0.0);
    }

    void paint(juce::Graphics& g) override
    {
        // Debug Grid Lines
        // Choose a colour for the grid lines
        bool debug = false;
		if (!debug) return;
        g.setColour(juce::Colours::grey);

        auto width = getWidth();
        auto height = getHeight();

        // Draw vertical grid lines: every 1/6 of the total width
        for (int i = 1; i < 6; ++i)
        {
            float x = (width * i) / 6.0f;
            g.drawLine(x, 0.0f, x, (float)height);
        }

        // Draw horizontal grid lines: every 1/4 of the total height
        for (int j = 1; j < 4; ++j)
        {
            float y = (height * j) / 4.0f;
            g.drawLine(0.0f, y, (float)width, y);
        }

        g.setColour(juce::Colours::red);
        //g.setColour(juce::Colour());
        drawSliderOutline(g, oscLevelSlider);
        drawSliderOutline(g, oscFineTuneSlider);
        drawSliderOutline(g, oscCoarseTuneSlider);
        drawSliderOutline(g, oscRatioSlider);
        drawSliderOutline(g, oscFeedbackSlider);
    }

    void resized() override
    {
        auto bounds = getLocalBounds();
        auto height = bounds.getHeight();
        auto width = bounds.getWidth();
        auto width_half = width / 2;
        auto width_3rd = width / 3;
        auto height_half = height / 2;
        auto height_3rd = height / 3;

        int small_knob_size = width_half / 3;
        int big_knob_size = width_half / 2;

        auto levelSliderArea = bounds;
        auto fineTuneSliderArea = bounds;
        auto coarseTuneSliderArea = fineTuneSliderArea;
        auto ratioSliderArea = fineTuneSliderArea;
        auto feedbackSliderArea = fineTuneSliderArea;

        levelSliderArea = levelSliderArea.removeFromBottom(height_half / 2).reduced(width_half / 3, 0).withSizeKeepingCentre(width_3rd * 2, height_half / 2);
        fineTuneSliderArea = fineTuneSliderArea.removeFromBottom(height).removeFromLeft(width_3rd - small_knob_size / 2).withSizeKeepingCentre(small_knob_size, small_knob_size);
        coarseTuneSliderArea = coarseTuneSliderArea.removeFromBottom(height).removeFromLeft(width_3rd + small_knob_size * 2).withSizeKeepingCentre(big_knob_size, big_knob_size);
        feedbackSliderArea = feedbackSliderArea.removeFromBottom(height).removeFromRight(width_3rd + big_knob_size * 2).withSizeKeepingCentre(big_knob_size, big_knob_size);
        ratioSliderArea = ratioSliderArea.removeFromBottom(height).removeFromRight(width_3rd).withSizeKeepingCentre(big_knob_size, big_knob_size);

        // Set bounds for each slider and label
        setSliderBounds(oscLevelSlider, oscLevelLabel, levelSliderArea);
        setSliderBounds(oscFineTuneSlider, oscFineTuneLabel, fineTuneSliderArea);
        setSliderBounds(oscCoarseTuneSlider, oscCoarseTuneLabel, coarseTuneSliderArea);
        setSliderBounds(oscRatioSlider, oscRatioLabel, ratioSliderArea);
        setSliderBounds(oscFeedbackSlider, oscFeedbackLabel, feedbackSliderArea);
    }

private:
    void initializeSlider(juce::Slider& slider, juce::Label& label, const juce::String& name, juce::Slider::SliderStyle style, double min, double max, double interval, double initialValue)
    {
        addAndMakeVisible(slider);
        slider.setSliderStyle(style);
        slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
        slider.setRange(min, max, interval);
        slider.setValue(initialValue);
        slider.addListener(this);
		slider.setDoubleClickReturnValue(true, initialValue);
        addLabel(slider, label, name);
    }

    void setSliderBounds(juce::Slider& slider, juce::Label& label, juce::Rectangle<int> bounds)
    {
        slider.setBounds(bounds);
        if(!slider.getSliderStyle() == juce::Slider::SliderStyle::LinearHorizontal)
            label.setBounds(bounds.withHeight(20).translated(0, -20).expanded(10, 0)); // Place the label above the slider
        else 
            label.setBounds(bounds.withHeight(20).translated(0, 20).expanded(10, 0));
    }

    void drawSliderOutline(juce::Graphics& g, juce::Slider& slider)
    {
        g.drawRect(slider.getBounds(), 2); // Draw a red outline with a thickness of 2
    }
    
    void addLabel(juce::Slider& slider, juce::Label& label, const juce::String& name)
    {
        label.setText(name + ": " + juce::String(slider.getValue()), juce::dontSendNotification);
        label.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(label);
    }

    void sliderValueChanged(juce::Slider* slider) override
    {
        if (slider == &oscLevelSlider)
            oscLevelLabel.setText("Level: " + juce::String(slider->getValue()), juce::dontSendNotification);
        else if (slider == &oscFineTuneSlider)
            oscFineTuneLabel.setText("Fine Tune: " + juce::String(slider->getValue()), juce::dontSendNotification);
        else if (slider == &oscCoarseTuneSlider)
            oscCoarseTuneLabel.setText("Coarse Tune: " + juce::String(slider->getValue()), juce::dontSendNotification);
        else if (slider == &oscRatioSlider)
            oscRatioLabel.setText("Ratio: " + juce::String(slider->getValue()), juce::dontSendNotification);
        else if (slider == &oscFeedbackSlider)
            oscFeedbackLabel.setText("Feedback: " + juce::String(slider->getValue()), juce::dontSendNotification);
    }

    juce::String tabTitle;

    juce::Slider oscLevelSlider;
    juce::Slider oscFineTuneSlider;
    juce::Slider oscCoarseTuneSlider;
    juce::Slider oscRatioSlider;
    juce::Slider oscFeedbackSlider;

    juce::Label oscLevelLabel;
    juce::Label oscFineTuneLabel;
    juce::Label oscCoarseTuneLabel;
    juce::Label oscRatioLabel;
    juce::Label oscFeedbackLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscTab)
};

class OscComp : public juce::TabbedComponent
{
public:
    OscComp(int tabDepth = 30);
    ~OscComp() override;
    void setTabDepth() { setTabBarDepth(getLocalBounds().getWidth() / 12); }
private:

    juce::Colour defaultTabColor = juce::Colours::palevioletred;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscComp)
};
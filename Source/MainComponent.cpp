/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Control.h"
#include "SerialConnection.h"

#define NUM_CTRLS 2

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public AudioAppComponent,
                               public ChangeListener
{
public:
    //==============================================================================
  MainContentComponent() : conn(SerialConnection())
    {
        setSize (800, 600);

        for (int i = 0; i < NUM_CTRLS; i++) {
            auto ctrl = std::make_shared<Control>(i);
            conn.addControl(ctrl);
            ctrl->addChangeListener(this);
        }

        conn.startThread();
        // specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }

    ~MainContentComponent()
    {
        shutdownAudio();
    }

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
        // This function will be called when the audio device is started, or when
        // its settings (i.e. sample rate, block size, etc) are changed.

        // You can use this function to initialise any resources you might need,
        // but be careful - it will be called on the audio thread, not the GUI thread.

        // For more details, see the help for AudioProcessor::prepareToPlay()
    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        // Your audio-processing code goes here!

        // For more details, see the help for AudioProcessor::getNextAudioBlock()

        // Right now we are not producing any data, in which case we need to clear the buffer
        // (to prevent the output of random noise)
        bufferToFill.clearActiveBufferRegion();
    }

    void releaseResources() override
    {
        // This will be called when the audio device stops, or when it is being
        // restarted due to a setting change.

        // For more details, see the help for AudioProcessor::releaseResources()
    }

    //==============================================================================
    void paint (Graphics& g) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

        // You can add your drawing code here!
    }

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
    }

    void changeListenerCallback(ChangeBroadcaster* source) override
    {
        if (const Control* ctrl = dynamic_cast<const Control*> (source)) {
          std::cout << "id: " << ctrl->id << "\n";
          std::cout << "val: " << ctrl->val << "\n";
          std::cout << "isOn: " << ctrl->isOn << "\n";
        } else {
            std::cout << "Unknown callback source\n";
        }
    }

private:
    //==============================================================================

    // Your private member variables go here...

    SerialConnection conn;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }

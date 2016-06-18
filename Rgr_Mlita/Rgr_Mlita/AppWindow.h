#pragma once
#include "stdafx.h"
#include "AppMenu.h"
#include <deque>
#include "Canvas.h"

class CAppWindow : public sf::RenderWindow
{
public:
    CAppWindow();
    ~CAppWindow();

    void EnterLoop();

private:
    enum class State
    {
        WaitingInput,
        RunningDemo,
        WaitingOutput,
    };

    void SetState(State state);
    void OnRunningDemo();
    bool SwitchNextFrame();
    void AskOpenInput();
    void AskSaveOutput();
	void DisplayHelp();
	void DisplayAboutAuthor();
	void RunDemo(std::ifstream &in);

    State m_state = State::WaitingInput;
    sf::Font m_font;
    std::unique_ptr<CAppMenu> m_menu;
    size_t m_openActionId = 0;
    size_t m_saveActionId = 0;
	size_t m_displayHelpActionId = 0;
	size_t m_aboutAuthorActionId = 0;
	float m_timer = 0;
	sf::Clock m_clock;
	std::unique_ptr<CCanvas> m_canvas;
};

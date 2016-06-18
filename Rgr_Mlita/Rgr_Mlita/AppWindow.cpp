#include "stdafx.h"
#include "AppWindow.h"
#include "tinyfiledialogs.h"
#include <boost/bind.hpp>
#include <boost/optional/optional_io.hpp>
#include "LabyrinthParser.h"
#include "LabyrinthController.h"

namespace
{
const unsigned WINDOW_WIDTH = 800;
const unsigned WINDOW_HEIGHT = 740;
const unsigned MENU_BAR_HEIGHT = 20;
const unsigned WINDOW_STYLE = sf::Style::Titlebar | sf::Style::Close;
}

CAppWindow::CAppWindow()
    : sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Labyrinth Painter", WINDOW_STYLE)
{
    m_menu = std::make_unique<CAppMenu>("Menu");
    m_menu->SetFrame(sf::FloatRect(0, 0, float(WINDOW_WIDTH), float(MENU_BAR_HEIGHT)));
    m_openActionId = m_menu->AddAction("Open file", std::bind(&CAppWindow::AskOpenInput, this));
    m_saveActionId = m_menu->AddAction("Save to file", std::bind(&CAppWindow::AskSaveOutput, this));
	m_displayHelpActionId = m_menu->AddAction("Display help", std::bind(&CAppWindow::DisplayHelp, this));
	m_aboutAuthorActionId = m_menu->AddAction("About author", std::bind(&CAppWindow::DisplayAboutAuthor, this));

    setFramerateLimit(60);
    setVerticalSyncEnabled(true);
    SetState(State::WaitingInput);

    m_font.loadFromFile("res/Ubuntu-R.ttf");
}

CAppWindow::~CAppWindow()
{
    m_menu.reset();
}

void CAppWindow::EnterLoop()
{
    while (isOpen())
    {
        sf::Event event;
        while (pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                close();
                return;
            }
            m_menu->OnEvent(event);
        }

        clear(sf::Color::White);
        if (m_state != State::WaitingInput && m_canvas)
        {
			OnRunningDemo();
			draw(m_canvas->GetDrawableObject());
        }
        draw(*m_menu);
        display();
    }
}

void CAppWindow::SetState(CAppWindow::State state)
{
    m_state = state;
    m_menu->SetActionEnabled(m_openActionId, state != State::RunningDemo);
	m_menu->SetActionEnabled(m_displayHelpActionId, state != State::RunningDemo);
    m_menu->SetActionEnabled(m_saveActionId, state == State::WaitingOutput);
	m_menu->SetActionEnabled(m_aboutAuthorActionId, state != State::RunningDemo);
}

void CAppWindow::OnRunningDemo()
{
    if (m_state == State::RunningDemo && (!SwitchNextFrame()))
    {
        SetState(State::WaitingOutput);
    }
}

bool CAppWindow::SwitchNextFrame()
{
	auto time = m_clock.getElapsedTime().asMilliseconds();
	m_clock.restart();
	m_timer += time;

	return m_canvas->OnUpdate(m_timer);
}

void CAppWindow::AskOpenInput()
{
    const char *filters[] = { "*.txt" };
    char const *result = tinyfd_openFileDialog("Select input file", "", 1, filters, "", false);

    if (result == nullptr)
    {
        return;
    }

    std::ifstream in(result);
    if (!in.is_open())
    {
        tinyfd_messageBox("Error", "I/O error when reading input file", "ok", "error", 1);
    }
    else
    {
		RunDemo(in);
    }
}

void CAppWindow::AskSaveOutput()
{
    const char *filters[] = { "*.txt" };
    char const *result = tinyfd_saveFileDialog("Select output file", "", 1, filters, "");
    if (!result)
    {
        return;
    }
    std::ofstream out(result);
    if (!out.is_open() || !m_canvas)
    {
        tinyfd_messageBox("Error", "I/O error when writing output file", "ok", "error", 1);
    }
    else
    {
		out << (m_canvas->GetOutput() - WALLS_COUNT) * WALL_AREA;
        tinyfd_messageBox("Success", "File saved OK", "ok", "info", 1);
    }
}

void CAppWindow::DisplayHelp()
{
	tinyfd_messageBox("Help", HELP_INFO.c_str(), "ok", "info", 1);
}

void CAppWindow::DisplayAboutAuthor()
{
	tinyfd_messageBox("About author", ABOUT_AUTHOR.c_str(), "ok", "info", 1);
}

void CAppWindow::RunDemo(std::ifstream & in)
{
	try
	{
		m_canvas.reset();
		m_canvas = CCanvas::Create(in);
		SetState(State::RunningDemo);
	}
	catch (std::invalid_argument const &err)
	{
		tinyfd_messageBox("Error", err.what(), "ok", "error", 1);
	}
	catch (...)
	{
		tinyfd_messageBox("Error", "Unknown error", "ok", "error", 1);
	}
}

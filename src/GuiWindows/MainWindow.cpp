//
// Created by Руслан Москвитин on 21.09.2024.
//

#include "MainWindow.h"

MainWindow::MainWindow(wxWindow *parent)  : wxFrame(parent, wxID_ANY, wxT("Broadcasting authomatisation programm"), wxPoint(50, 50), wxSize(1285, 850))
{

    //Переключатель между сервисами (телеканалами)
    сhannelsSwitcher = new wxNotebook(this, wxID_ANY, wxPoint(0, 0), wxDefaultSize, 0, _T("ID_NOTEBOOK1"));

    //Создаем фейковый сервис и добавляем его в переключатель через выделенный метод
    Channel *service = new Channel();
    service->setName("Телеканал Четверг");
    appendServiceToTab(service);

    Channel::testSQL();
}


wxScrolledWindow MainWindow::appendServiceToTab(Channel* broadcastedService) {
    // Создаем панель для вкладки
    wxPanel* tabPanel = new wxPanel(сhannelsSwitcher, wxID_ANY);

    // Создаем текстовое поле для вкладки
    wxTextCtrl* textCtrl = new wxTextCtrl(tabPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);

    // Создаем компоновщик для панели вкладки
    wxBoxSizer* tabSizer = new wxBoxSizer(wxVERTICAL);
    tabSizer->Add(textCtrl, 1, wxEXPAND);
    tabPanel->SetSizerAndFit(tabSizer);

    // Добавляем вкладку в записную книжку
    сhannelsSwitcher->AddPage(tabPanel, wxString::Format(broadcastedService->getName()));

    return tabPanel;
}

MainWindow::~MainWindow()
{

}
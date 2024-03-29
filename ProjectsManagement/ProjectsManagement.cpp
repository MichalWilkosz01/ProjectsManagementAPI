﻿#include <iostream>

#include "CustomAllocator.h"
#include "User.h"
#include "ProjectManager.h"
#include "FileHandler.h"
#include "Project.h"


int main()
{

    ProjectManager* projectManager = ProjectManager::getInstance();
    Project* storeApplication = projectManager->createProject("Store application in .NET", "Creating an application for a clothing store", Date(1, 3, 2024, 00, 00), Date(30, 7, 2024, 00, 00));
    Task* database = projectManager->assignTaskToProject("Prepare Databse structure", "Prepare database strcuture for store using Entity Framework Core", Date(1, 3, 2024, 00, 00), Date(30, 3, 2024, 00, 00),*storeApplication);
    Task* API = projectManager->assignTaskToProject("Prepare API", "Write an API for entities", Date(1, 4, 2024, 00, 00), Date(30, 4, 2024, 00, 00), *storeApplication);
    Task* basic = projectManager->assignTaskToProject("Write basic functionalities", "Create authorization and authentication mechanism", Date(1, 5, 2024, 00, 00), Date(30, 5, 2024, 00, 00), *storeApplication);
    Task* adv = projectManager->assignTaskToProject("Write advanced functionalities", "Create pay mechanism", Date(1, 6, 2024, 00, 00), Date(30, 6, 2024, 00, 00),*storeApplication);
    Task* GUI = projectManager->assignTaskToProject("Make nice looking GUI", "Create GUI", Date(1, 7, 2024, 00, 00), Date(15, 7, 2024, 00, 00), *storeApplication);
    Task* tests = projectManager->assignTaskToProject("Test application", "Write tests for application", Date(15, 7, 2024, 00, 00), Date(30, 7, 2024, 00, 00),*storeApplication);
    User* programista1 = new User("Michal", "Wilkosz", "michalwilkosz1234@wp.pl", "michwil", "515515515");
    User* programista2 = new User("Kamil", "Surlas", "kamilsurlas1234@wp.pl", "kamsur");
    User* programista3 = new User("Marcin", "Kowalski", "marcinkowalski@wp.pl", "markow");
    User* programista4 = new User("Bartosz", "Nowak", "bartosznowak@wp.pl", "barnow");

    User* kierownik1 = new User("Michal", "Kowalski", "michalkowalski@wp.pl", "michkow");
    User* kierownik2 = new User("Szymon", "Dziendzielowski", "szymondziendzielowski@wp.pl", "szydzi", "515515515");

    projectManager->assignManagerToProject(*storeApplication,*kierownik2);
    projectManager->assignUserToProject(*storeApplication, *programista1);
    projectManager->assignUserToProject(*storeApplication, *programista2);
    projectManager->assignUserToProject(*storeApplication, *programista3);
    projectManager->assignUserToProject(*storeApplication, *programista4);

    projectManager->assignLeaderToTask(*storeApplication, *database, *programista1);
    projectManager->assignLeaderToTask(*storeApplication, *database, *programista3);
    projectManager->assignUserToTask(*storeApplication, *database, *programista2);

    projectManager->assignLeaderToTask(*storeApplication, *API, *programista1);
    projectManager->assignLeaderToTask(*storeApplication, *API, *programista3);
    projectManager->assignUserToTask(*storeApplication, *API, *programista2);

    projectManager->assignLeaderToTask(*storeApplication, *basic, *programista1);
    projectManager->assignLeaderToTask(*storeApplication, *basic, *programista3);
    projectManager->assignUserToTask(*storeApplication, *basic, *programista4);

    projectManager->assignLeaderToTask(*storeApplication, *adv, *programista1);
    projectManager->assignLeaderToTask(*storeApplication, *adv, *programista3);
    projectManager->assignUserToTask(*storeApplication, *adv, *programista2);
    projectManager->assignUserToTask(*storeApplication, *adv, *programista4);
    
    projectManager->assignLeaderToTask(*storeApplication, *GUI, *programista2);
    projectManager->assignUserToTask(*storeApplication, *GUI, *programista4);

    projectManager->assignLeaderToTask(*storeApplication, *tests, *programista3);
    projectManager->assignUserToTask(*storeApplication, *tests, *programista4);

    Project* nowy = projectManager->createProject("xd", "Creating an application for a clothing store", Date(1, 3, 2024, 00, 00), Date(30, 7, 2024, 00, 00));
    Task* backend = projectManager->assignTaskToProject("Backend", "Create GUI", Date(1, 7, 2024, 00, 00), Date(15, 7, 2024, 00, 00), *nowy);
    
    projectManager->assignUserToProject(*nowy, *programista1);
    projectManager->assignUserToProject(*nowy, *programista2);
    projectManager->assignLeaderToTask(*nowy, *backend, *programista1);
    projectManager->assignUserToTask(*nowy, *backend, *programista2);
 
    
 
    FileHandler::saveCSVFile();
    FileHandler::saveFile(projectManager->getProjects());
  
    delete programista1;
    delete programista2;
    delete programista3;
    delete programista4;
    delete kierownik1;
    delete kierownik2;
}


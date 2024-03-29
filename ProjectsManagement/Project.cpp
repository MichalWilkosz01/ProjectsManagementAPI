#include "Project.h"
#include "CustomException.h"


Project::Project(const std::string& name, const std::string& desc, Date projectStartDate, Date projectFinishDate)
	:TaskProject(name,desc,projectFinishDate,projectFinishDate)
{

}



void Project::addTask(Task& task)
{
	if (m_finishDate < task.getFinishDate() || m_creationDate > task.getCreationDate())
	{
		throw invalid_task("Provided task date (" + task.getFinishDate().getDateAsString() + ") is invalid (Project start date: " +m_startDate.getDateTimeAsString()+" project finish date : " + m_finishDate.getDateTimeAsString() + ")");
	}
	m_tasks.addElement(&task);
}
bool Project::removeTask(Task& task)
{
	for (size_t i = 0; i < task.getAllLeaders().getSize(); i++)
	{
		task.removeLeader(*task.getAllLeaders()[i]);
	}
	for (size_t i = 0; i < task.getAllUsers().getSize(); i++)
	{
		task.removeUser(*task.getAllUsers()[i]);
	}
	return m_tasks.deleteElement(&task);
}

void Project::removeAllTasks()
{
	m_tasks.removeAll();
}

void Project::addUser(User& user)
{
	m_users.addElement(&user);
}

User* Project::removeUser(const User& usr)
{
	return m_users.removeElement(&usr);
}

void Project::assignManager(User& manager)
{
	if (m_manager == nullptr)
	{
		m_manager = &manager;
	}
}

bool Project::removeManager()
{
	if (m_manager != nullptr)
	{
		m_manager = nullptr;
		return true;
	}
	return false;
}

void Project::assignUserToTask(Task& task, User& user)
{
	if (m_users.isAssigned(&user))
		task.addUser(user);
	else
		throw invalid_user("User is not assigned to project");
}

User* Project::removeUserFromTask(Task& task, User& user)
{
	return task.removeUser(user);
}

void Project::assignLeaderToTask(Task& task, User& leader)
{
	if (m_users.isAssigned(&leader))
		task.addLeader(leader);
	else
		throw invalid_user("User is not assigned to project");
}

User* Project::removeLeaderFromTask(Task& task, User& leader)
{
	return task.removeLeader(leader);
}

void Project::changeTaskStartDate(Task& task, Date newDate)
{
	if (m_startDate > newDate)
		throw invalid_date("Provided task's date is earlier than project's date");
	task.setStartDate(newDate);
}

void Project::changeTaskFinishDate(Task& task, Date newDate)
{
	if (m_finishDate < newDate)
		throw invalid_date("Provided task's date is later than project's date");
	task.setFinishDate(newDate);
}

string Project::print()
{
	string formattedText;
	
	formattedText += "Project name: " + this->m_name + "\n";
	if (m_manager != nullptr)
	{
		formattedText += "Project manager:; " + this->m_manager->toString() + "\n";
	}
	formattedText += "All participants:\n";
	formattedText += "Imie;Nazwisko;Nick;Adres mail;Numer telefonu\n";
	for (int i = 0; i < this->m_users.getSize(); i++) {
		formattedText += m_users[i]->toString() + "\n";
	}

	formattedText += "\nTasks:";
	for (size_t i = 0; i < this->m_tasks.getSize(); i++)
	{
		formattedText += m_tasks[i]->toString();
	}

	return formattedText;
}


CustomAllocator<User>& Project::getAllParticipants()
{
	
		return m_users;
	
}

CustomAllocator<Task>& Project::getTasks()
{

		return m_tasks;
	
}
User* Project::getManager()
{
	return m_manager;
}
bool Project::operator==(const Project& project)
{
	return m_name == project.m_name &&
		m_description == project.m_description &&
		m_startDate == project.m_startDate &&
		m_finishDate == project.m_finishDate;
}

bool Project::operator!=(const Project& project)
{
	return !(*this == project);
}


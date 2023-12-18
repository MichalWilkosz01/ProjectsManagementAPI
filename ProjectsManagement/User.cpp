#include "User.h"

User::User(string name, string surname, string mail, string username, string phoneNumber, Task* task)
	:User(name, surname, mail, username, phoneNumber)
{
	assignTask(task);
}

User::User(string name, string surname, string mail, string username, string phoneNumber)
	:User(name, surname, mail, username)
{
	setPhoneNumber(phoneNumber);
}

User::User(string name, string surname, string mail, string username)
{
	setName(name);
	setSurname(surname);
	setMail(mail);
	setUsername(username);
}

//Public
void User::setName(const string& newName)
{
	isValidName(newName) ? m_name = newName : throw invalid_argument("Wrong name (too short or too long or invalid characters)");
}

void User::setSurname(const string& newSurname)
{
	isValidName(newSurname) ? m_surname = newSurname : throw invalid_argument("Wrong surname (too short or too long or invalid characters)");
}

void User::setMail(const string& newMail)
{
	isValidMail(newMail) ? m_mail = newMail : throw invalid_argument("Wrong email format");
}

void User::setUsername(const string& newUsername)
{
	isValidUsername(newUsername) ? m_username : throw invalid_argument("Wrong username");
}

void User::setPhoneNumber(const string& newPhoneNumber)
{
	isValidPhoneNumber(newPhoneNumber) ?
		m_phoneNumber = newPhoneNumber : throw invalid_argument("Wrong phone number");
}

void User::assignTask(Task* task)
{
	if (task == nullptr)
		throw std::invalid_argument("Cannot assign task that is null");

	isUserUnassignedFromTask(task) ? m_tasks.push_back(task) : throw std::invalid_argument("User is already participating in task");
}





//Private
bool User::isValidName(const string& name)
{
	// Check if the name contains only letters (including characters like ��) 
	// and has a length between 2 and 30 characters.
	string pattern = "^[\\p{L}]{2,30}$";
	const regex nameRegex(pattern);

	return regex_match(name, nameRegex);
}

bool User::isValidSurname(const string& surname)
{
	string pattern = "^[\\p{L}-]{2,50}$";
	const regex surnameRegex(pattern);

	return regex_match(surname, surnameRegex);
}

bool User::isValidMail(const string& mail)
{
	string pattern = "^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$";
	const regex mailRegex(pattern);

	return regex_match(mail, mailRegex);
}

bool User::isValidUsername(const string& username)
{
	constexpr size_t minLength = 2;
	constexpr size_t maxLength = 30;

	return (username.length() >= minLength && username.length() <= maxLength);
}

bool User::isValidPhoneNumber(const string& phoneNumber)
{
	//Check if phone number has the correct length and contains only digits
	return phoneNumber.length() == 9 && phoneNumber.find_first_not_of("0123456789") == string::npos;
}

bool User::isUserUnassignedFromTask(const Task* task)
{
	return std::find(m_tasks.begin(), m_tasks.end(), task) == m_tasks.end();
}


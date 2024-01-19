#pragma once
class ContextMenuItem
{
private:
	string m_name;
	string m_text;
	std::function<void()> m_action;

public:

	virtual void SetName(string name) {
		m_name = name;
	}

	virtual string GetName() {
		return m_name;
	}

	virtual void SetText(string text) {
		m_text = text;
	}

	virtual string GetText() {
		return m_text;
	}

	virtual void SetAction(std::function<void()> action) {
		m_action = action;
	}

	virtual std::function<void()> GetAction() {
		return m_action;
	}

	virtual void CallAction() {
		this->m_action();
	}

	static shared_ptr<ContextMenuItem> CreateContextMenuItem(string name, string text, std::function<void()> action);
};


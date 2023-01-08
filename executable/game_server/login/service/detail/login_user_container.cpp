#include "login_user_container.h"

namespace cebreiro::login
{
	bool LoginUserContainer::Contains(int64_t id) const
	{
		return _idIndexer.contains(id);
	}

	bool LoginUserContainer::Contains(const std::string& account) const
	{
		return _accountIndexer.contains(account);
	}

	void LoginUserContainer::Add(LoginUser item)
	{
		assert(!_idIndexer.contains(item.id));
		assert(!_accountIndexer.contains(item.account));

		auto temp = std::make_shared<LoginUser>(std::move(item));

		_users.push_back(temp);
		_idIndexer[temp->id] = temp;
		_accountIndexer[temp->account] = temp;
	}

	void LoginUserContainer::Remove(int64_t id)
	{
		auto iter = _idIndexer.find(id);
		if (iter == _idIndexer.end())
		{
			return;
		}

		std::string account = iter->second->account;

		std::erase_if(_users, [id](const std::shared_ptr<LoginUser>& user)
			{
				return user->id == id;
			});
		_idIndexer.erase(id);
		_accountIndexer.erase(account);
	}

	void LoginUserContainer::Remove(const std::string& account)
	{
		auto iter = _accountIndexer.find(account);
		if (iter == _accountIndexer.end())
		{
			return;
		}

		Remove(iter->second->id);
	}

	auto LoginUserContainer::Find(int64_t id) const -> LoginUser*
	{
		auto iter = _idIndexer.find(id);
		return iter != _idIndexer.end() ? iter->second.get() : nullptr;
	}

	auto LoginUserContainer::Find(const std::string& account) const -> LoginUser*
	{
		auto iter = _accountIndexer.find(account);
		return iter != _accountIndexer.end() ? iter->second.get() : nullptr;
	}

	auto LoginUserContainer::Find(std::array<int32_t, 2> token) const -> LoginUser*
	{
		auto iter = sr::find_if(_users, [token](const std::shared_ptr<LoginUser>& user)
			{
				return user->gatewayAuthenticationToken && user->gatewayAuthenticationToken == token;
			});
		return iter != _users.end() ? iter->get() : nullptr;
	}

	void LoginUserContainer::Foreach(const std::function<void(LoginUser&)>& fn)
	{
		auto view = _users | srv::transform([](const std::shared_ptr<LoginUser>& user) -> LoginUser&
			{
				return *user;
			});
		std::ranges::for_each(view, fn);
	}
}

#pragma once
#include <iostream>
#include <vector>
#include <functional>


//For class member functions
#define BIND_MEMBER_FUNC_0(instance, func) std::bind(&func,instance) //no parameter
#define BIND_MEMBER_FUNC(instance, func)  BIND_MEMBER_FUNC_0(instance, func) //no parameter
#define BIND_MEMBER_FUNC_1(instance, func) std::bind(&func, instance, std::placeholders::_1) //1 Parameter
#define BIND_MEMBER_FUNC_2(instance, func) std::bind(&func, instance, std::placeholders::_1,std::placeholders::_2) //2 Parameters
#define BIND_MEMBER_FUNC_3(instance, func) std::bind(&func, instance, std::placeholders::_1,std::placeholders::_2,std::placeholders::_3) //3 Parameters
#define BIND_MEMBER_FUNC_4(instance, func) std::bind(&func, instance, std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4) //4 Parameters

#define ACTION_VOID //for better looking

template<typename... Args>
class Action
{
private:
    std::vector<std::function<void(Args...)>> Listeners;

public:
   
    void Invoke(Args... args)
    {
        for (auto& listener : Listeners) {
            listener(args...);
        }
    }

    void AddListener(const std::function<void(Args...)>& func)
    {
        Listeners.push_back(func);
    }

    void RemoveListener(const std::function<void(Args...)>& func)
    {
        auto iterator = Listeners.begin();
        auto it = std::find_if(Listeners.begin(), Listeners.end(),
            [&func](const std::function<void(Args...)>& element) {
                return element.target<void(Args...)>() == func.target<void(Args...)>();
            });

        if (it != Listeners.end())
        {
            Listeners.erase(it);
        }
    }

    void operator += (const std::function<void(Args...)>& func) {
        AddListener(func);
    }


    void operator -= (const std::function<void(Args...)>& func) {
        RemoveListener(func);
    }

    void operator ()(Args... args)
    {
        Invoke(args...);
    }
};


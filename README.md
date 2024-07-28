# C++ Action Implementation

This project provides a C++ implementation of C#-style Actions using variadic templates and `std::function`. The `Action` template class allows for adding, removing, and invoking listeners with varying numbers of arguments.

## Usage

### Defining an Action

You can define an Action with any number of arguments using the `Action` template class.

```cpp
// Action with no arguments
Action<ACTION_VOID> action0;
//or Action<> action0;

// Action with one argument
Action<int> action1;

// Action with two arguments
Action<int, std::string> action2;
```


### Adding Listeners
Listeners can be added using the AddListener method or the += operator.
```cpp
// Adding a lambda function as a listener
action1 += [](int value) { std::cout << "Value: " << value << std::endl; };

// Adding a free function
void FreeFunction(int value) {
    std::cout << "Free Function Value: " << value << std::endl;
}
action1 += FreeFunction;
```

### Removing Listeners
Listeners can be removed using the RemoveListener method or the -= operator.
```cpp
action1 -= FreeFunction;
```

### Invoking Listeners
Listeners can be invoked using the Invoke method or the () operator.
```cpp
action1(42); // This will call all the listeners added to action1 with the argument 42
```

## Example Usage
### Class Member Functions
For class member functions, you can use the provided macros to bind the member functions.
```cpp
class MyClass {
public:
    void MemberFunctionNoArgs() {
        std::cout << "Member function with no arguments" << std::endl;
    }

    void MemberFunctionWithArgs(int value) {
        std::cout << "Member function with value: " << value << std::endl;
    }
};

int main()
{
MyClass instance;

Action<ACTION_VOID> actionNoArgs;
actionNoArgs += BIND_MEMBER_FUNC_0(&instance, MyClass::MemberFunctionNoArgs);

Action<int> actionWithArgs;
actionWithArgs += BIND_MEMBER_FUNC_1(&instance, MyClass::MemberFunctionWithArgs);
return 0;
}
```
### Non-member Functions
For non-member functions, you can directly add them as listeners.
```cpp
void NonMemberFunction(int value) {
    std::cout << "Non-member function with value: " << value << std::endl;
}

int main()
{
Action<int> action;
action += NonMemberFunction; //or action.AddListener(NonMemberFunction); - Both The Same
action(1); //or action.Invoke(1); - Both The Same
action -= NonMemberFunction; //or action.RemoveListener(NonMemberFunction); - Both The Same
return 0;
}
```
### Macros for Binding Member Functions
The provided macros simplify the binding of member functions to actions.

- BIND_MEMBER_FUNC_0(instance, func) for member functions with no parameters.
- BIND_MEMBER_FUNC_1(instance, func) for member functions with one parameter.
- BIND_MEMBER_FUNC_2(instance, func) for member functions with two parameters.
- BIND_MEMBER_FUNC_3(instance, func) for member functions with three parameters.
- BIND_MEMBER_FUNC_4(instance, func) for member functions with four parameters

You can also use `std::bind` instead.
```cpp
class Example {
public:
    void Print() {
        std::cout << "Hello, World!" << std::endl;
    }

    void PrintNumber(int num) {
        std::cout << "Number: " << num << std::endl;
    }
};

int main()
{
Example ex;

Action<> actionPrint;
actionPrint += BIND_MEMBER_FUNC_0(&ex, Example::Print);

Action<int> actionPrintNumber;
actionPrintNumber += BIND_MEMBER_FUNC_1(&ex, Example::PrintNumber);

actionPrint();           // Output: Hello, World!
actionPrintNumber(100);  // Output: Number: 100
return 0;
}
```
## License
This project is licensed under the MIT License. See the LICENSE file for details.

#pragma once

#ifdef TR_PLATFORM_WINDOWS
	#ifdef TR_BUILD_DLL
		#define TR_API _declspec(dllexport)
	#else
		#define TR_API _declspec(dllimport)
	#endif
#else
	#error Trengine only supports Windows!
#endif

#ifdef TR_PLATFORM_WINDOWS
	#define CREATE_WINDOW() std::unique_ptr<Window>(&Trengine::WindowsWindow(Trengine::WindowProps()))
#else
	#define CREATE_WINDOW() std::unique_ptr<Window>(nullptr)
#endif


#define BIT(x) (1 << x)

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type;}\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}\

#ifdef TR_ENABLE_ASSERTS
	#define TR_ASSERT(x, ...) {if (!(x)) { TR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define TR_CORE_ASSERT(x, ...) {if (!(x)) { TR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define TR_ASSERT(x, ...)
	#define TR_CORE_ASSERT(x, ...)
#endif
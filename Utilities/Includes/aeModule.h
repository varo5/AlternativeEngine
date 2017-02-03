#pragma once

namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* @class	Module
	/*
	/* @brief	Represents one engine module. Essentially it is a specialized type of singleton. 
	/* 			Module be manually started up and shut down before and after use.
	/*
	/* @tparam	T	Generic type parameter.
	/*************************************************************************************************/

	template<class T>
	class Module
	{
	public:
		/*************************************************************************************************/
		/* @fn	static T& Module::Instance()
		/*
		/* @brief	Returns a reference to the module instance. Module has to have been started up first,
		/* 			 otherwise an exception will be thrown.
		/*
		/* @return	A reference to a T.
		/*************************************************************************************************/

		static T& Instance()
		{
			if (IsShutDown())
			{
				AE_EXCEPT(InternalErrorException, "Trying to access a module but it hasn't been started up yet.");
			}

			return *_Instance();
		}

		/*************************************************************************************************/
		/* @fn	static T* Module::InstancePtr()
		/*
		/* @brief	Returns a pointer to the module instance. Module hast to have been started up first
		/* 			otherwise an exception will be thrown.
		/*
		/* @return	null if it fails, else a pointer to a T.
		/*************************************************************************************************/

		static T* InstancePtr()
		{
			if (IsShutDown())
			{
				AE_EXCEPT(InternalErrorException, "Trying to access a module but it hasn't been started up yet.");
			}

			return _Instance();
		}

		/*************************************************************************************************/
		/* @fn	template<class... Args> static void Module::StartUp(Args&&... args)
		/*
		/* @brief	Constructs and starts the module using the specified parameters.
		/*
		/* @tparam	Args	Type of the arguments.
		/* @param	args	Variable arguments providing [in,out] The arguments.
		/*************************************************************************************************/

		template<class... Args>
		static void StartUp(Args&&... args)
		{
			if (!IsShutDown())
			{
				AE_EXCEPT(InternalErrorException, "Trying to start an already started module.");
			}

			_Instance() = ae_new<T>(std::forward<Args>(args)...);
			IsShutDown() = false;

			((Module*)_Instance())->OnStartUp();
		}

		/*************************************************************************************************/
		/* @fn	template<class SubType, class... Args> static void Module::StartUp(Args&&... args)
		/*
		/* @brief	Constructs and starts a specialized type of module. Provided type must derive form
		/* 			type the module is initialized with.
		/*
		/* @tparam	SubType	Type of the sub type.
		/* @tparam	Args   	Type of the arguments.
		/* @param	args	Variable arguments providing [in,out] The arguments.
		/*************************************************************************************************/

		template<class SubType, class... Args>
		static void StartUp(Args&&... args)
		{
			static_assert(std::is_base_of<T, SubType>::value, "Provided type is not derived from type the Module is initialized with.");

			if (!IsShutDown())
			{
				AE_EXCEPT(InternalErrorException, "Trying to start an already started module.");
			}

			_Instance() = ae_new<T>(std::forward<Args>(args)...);
			IsShutDown() = false;

			((Module*)_Instance())->OnStartUp();
		}

		/*************************************************************************************************/
		/* @fn	static void Module::ShutDown()
		/*
		/* @brief	Shuts down this module and frees any resources it is using.
		/*************************************************************************************************/

		static void ShutDown()
		{
			if (IsShutDown() || IsDestroyed())
			{
				AE_EXCEPT(InternalErrorException, "Trying to shut down an already shut down module.");
			}

			((Module*)_Instance())->OnShutDown();

			ae_delete(_Instance());
			IsShutDown() = true;			
		}

		/*************************************************************************************************/
		/* @fn	static bool Module::IsStarted()
		/*
		/* @brief	Query if the module has been started.
		/*
		/* @return	true if started, false if not.
		/*************************************************************************************************/

		static bool IsStarted()
		{
			return !IsShutDown() && !IsDestroyed();
		}

	protected:
		Module()
		{
		}

		virtual ~Module()
		{
			_Instance() = nullptr;
			IsDestroyed() = true;
		}

		Module(const Module&)
		{
		}

		Module& operator=(const Module&)
		{
			return *this;
		}

		/*************************************************************************************************/
		/* @fn	virtual void Module::OnStartUp()
		/*
		/* @brief	Override if you want to module to be notified once it has been constructed on start.
		/*************************************************************************************************/

		virtual void OnStartUp()
		{

		}

		/*************************************************************************************************/
		/* @fn	virtual void Module::OnShutDown()
		/*
		/* @brief	Override if you want to module to be notified once it has been constructed on shut
		/* 			down.
		/*************************************************************************************************/

		virtual void OnShutDown()
		{

		}

		/*************************************************************************************************/
		/* @fn	static T*& Module::_Instance()
		/*
		/* @brief	Returns instance to the object.
		/*
		/* @return	null if it fails, else a reference to a T*.
		/*************************************************************************************************/

		static T*& _Instance()
		{
			static T* inst = nullptr;
			return inst;
		}

		/*************************************************************************************************/
		/* @fn	static bool& Module::IsDestroyed()
		/*
		/* @brief	Checks has the module been shut down.
		/*
		/* @return	A reference to a bool.
		/*************************************************************************************************/

		static bool& IsDestroyed()
		{
			static bool inst = false;
			return inst;
		}

		/*************************************************************************************************/
		/* @fn	static bool& Module::IsShutDown()
		/*
		/* @brief	Checks has the module been started up.
		/*
		/* @return	A reference to a bool.
		/*************************************************************************************************/

		static bool& IsShutDown()
		{
			static bool inst = true;
			return inst;
		}
	}; 
}

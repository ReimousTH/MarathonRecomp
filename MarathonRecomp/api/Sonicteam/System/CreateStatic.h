#pragma once
namespace Sonicteam{

	namespace System{

		template <typename T>
		class CreateStatic {
		public:
			static T* Create() {	
				static T _value;
				return &_value;
			}
		};
	};
};


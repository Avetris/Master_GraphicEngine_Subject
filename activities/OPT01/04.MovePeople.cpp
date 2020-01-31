
// --------------------- vector3 --------------------
class vector3
{
	public:
		vector3() : mX(0.0f), mY(0.0f), mZ(0.0f) {}
		vector3(float x, float y, float z) : mX(x), mY(y), mZ(z) {}
		~vector3() {}

		vector3 operator+(const vector3 &right)
		{
			vector3 temp;
			temp.mX = mX + right.mX;
			temp.mY = mY + right.mY;
			temp.mZ = mZ + right.mZ;

			return temp;
		}

		bool operator !=(const vector3 &right)
		{
			if ((mX != right.mX) ||
				(mY != right.mY) ||
				(mZ != right.mZ))
			{
				return false;
			}

			return true;
		}

		void SetX(float x)		{ mX = x; }
		void SetY(float y)		{ mY = y; }
		void SetZ(float z)		{ mZ = z; }
	
	private:
		float mX;
		float mY;
		float mZ;
};

// --------------------- Person --------------------
class Person
{
	public: 
		Person() 
		{ 
			memset(mName, 0, 255);
			mNext = NULL;
			mMale = false;
			mPosition.SetX(0.0f);
			mPosition.SetY(0.0f);
			mPosition.SetZ(0.0f);
			mId = sUniqueId++;
		}

		~Person() {}

		bool operator !=(const Person &right)
		{
			if ((memcmp(mName, right.mName, 255) != 0) ||
				(mMale != right.mMale) ||
				(mPosition != right.mPosition) ||
				(mId != right.mId) ||
				(mNext != right.mNext))
			{
				return true;
			}

			return false;
		}

		char	mName[255];
		bool	mMale;
		vector3 mPosition;
		int     mId;
		Person *mNext;

		static  int sUniqueId;
};

int Person::sUniqueId = 0;

// --------------------- AI --------------------
class AI
{
	public:
		AI();
		~AI()		{}
		Person* GetFirstPerson();
		Person* GetNextPerson(Person person);
		Person* GetFirstNonMovingPerson();
		void MovePeople(bool moveLeft);
	private:
		Person *mPersonList;
};

AI::AI()
{
	mPersonList = new Person;
	Person *person = mPersonList;
	for (int i = 0; i < 1000; i++)
	{
		person->mNext = new Person;
		person = person->mNext;
	}
}

Person* AI::GetFirstPerson()
{
	return mPersonList;
}

Person* AI::GetNextPerson(Person person)
{
	return person.mNext;
}

Person* AI::GetFirstNonMovingPerson()
{
	Person *person = mPersonList;
    // the first 500 people are moving, the second 500 are not moving
	while (person->mId < 500)
	{
		person = person->mNext;
	}

	return person;
}

void AI::MovePeople(bool moveLeft)
{
	Person* firstNonMovingPerson = GetFirstNonMovingPerson(); // The first change is to obtain the first non moving person only one. If it is called GetFirstNonMovingPerson() in every loop iteration, it is checked the person in each time, which execute the while to find the first nonMovinPerson 500 times (until reach the first one). On this way, it will be increase the performance of the CPU.
	vector3 moveAmount; // If it is initialize and storage the moveAmount variable out of the loop, it will only initialize one, saving a lot of MEMORY.
	moveAmount.SetY(10);
	moveAmount.SetZ(10);
	for (Person* person = GetFirstPerson(); person != firstNonMovingPerson; person = GetNextPerson(*person))
	{
		if (moveLeft)
		{
			moveAmount.SetX(-10);

			person->mPosition = person->mPosition + moveAmount;
		}
		else
		{
			moveAmount.SetX(10);

			person->mPosition = person->mPosition + moveAmount;
		}
	}
	delete moveAmount; // In addition to initialize out of the loop moveAmount variable, it has to be deleted in each frame to also save MEMORY.
}

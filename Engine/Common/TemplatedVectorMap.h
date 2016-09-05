#pragma once

#ifndef _TEMPLATED_VECTOR_MAP_MANAGER_H
#define _TEMPLATED_VECTOR_MAP_MANAGER_H

#include <string>
#include <vector>
#include <map>

#include "Types.h"
#include "Logger\Logger.h"

template <class T>
class CTemplatedVectorMap
{
    public:
        class CMapResourceValue
        {
            public:
                T     mPtr;
                uint32 mIdx;

                CMapResourceValue(T value, uint32 aIdx)
                    : mPtr(value)
                    , mIdx(aIdx)
                {
                }

                CMapResourceValue()
                    : mPtr(nullptr)
                    , mIdx(0)
                {
                }
        };

        typedef std::vector<T>                           TVectorResources;
        typedef std::map<std::string, CMapResourceValue> TMapResources;

    protected:
        TVectorResources    mResVec;
        TMapResources       mResMap;

    public:
        CTemplatedVectorMap() { }
        virtual ~CTemplatedVectorMap()
        {
            Destroy();
        }

		const size_t Size() const
		{
			return mResVec.size();
		}

        bool Exist( const std::string & Name )
        {
            return mResMap.find( Name ) != mResMap.end();
        }

        void Remove( const std::string& Name )
        {
            TMapResources::iterator it = mResMap.find(Name);

			if (it != mResMap.end())
			{
				uint32 lIdx = it->second.mIdx;
				mResMap.erase(it);
				mResVec.erase(mResVec.begin() + lIdx);
				for (uint32 i = lIdx; i < mResVec.size(); ++i)
				{
					T l_TElement = mResVec[i];
					TMapResources::iterator l_ItMap = mResMap.begin();
					while (l_ItMap->second.mPtr != l_TElement)
						++l_ItMap;
					l_ItMap->second.mIdx = i;
				}
			}
        }

        virtual T operator[](size_t aIdx) const
        {
            return (mResVec.size() > aIdx) ? mResVec[aIdx] : 0;
        }

        virtual T operator[](const std::string& Name) const
        {
            TMapResources::const_iterator it = mResMap.find(Name );
            return (it != mResMap.end()) ? it->second.mPtr : 0;
        }

        virtual bool PushBack( const std::string& Name, T Resource )
        {
            bool lOk = false;

            if (mResMap.find(Name) == mResMap.end() )
            {
                CMapResourceValue lRes(Resource, (uint32)mResVec.size());
                mResVec.push_back(Resource);
                mResMap[Name] = lRes;
                lOk = true;
            }

            return lOk;
        }

        virtual void Destroy()
        {
			CheckedDelete(mResVec);
			Clear();
        }

        void Clear()
        {
            mResVec.clear();
            mResMap.clear();
        }
};

#endif
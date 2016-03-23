#pragma once

#ifndef _TEMPLATED_VECTOR_MAP_MANAGER_H
#define _TEMPLATED_VECTOR_MAP_MANAGER_H

#include <string>
#include <vector>
#include <map>

#include "Types.h"
#include "Logger\Logger.h"

template <class T> class CTemplatedVectorMapManager
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

        typedef std::vector<T>                          TVectorResources;
        typedef std::map<std::string, CMapResourceValue> TMapResources;

    protected:
        TVectorResources    mResVec;
        TMapResources       mResMap;

    public:
        CTemplatedVectorMapManager() { }
        virtual ~CTemplatedVectorMapManager()
        {
            Destroy();
        }

        bool Exist( const std::string & Name )
        {
            return mResMap.find( Name ) != mResMap.end();
        }

        void RemoveResource( const std::string& Name )
        {
            TMapResources::iterator it = mResMap.find(Name);

            if ( it == mResMap.end() )
            {
                return;
            }

            uint32 lIdx = it->second.mIdx;

            mResMap.erase(it);
            mResVec.erase(mResVec.begin() + lIdx);

            for (uint32 i =  lIdx; i < mResVec.size();  ++i)
            {
                T l_TElement = mResVec[i];
                TMapResources::iterator l_ItMap = mResMap.begin();

                while (l_ItMap->second.mPtr != l_TElement)
                {
                    ++l_ItMap;
                }

                l_ItMap->second.mIdx = i;
            }
        }

        virtual T GetResourceByaIdx(uint32 aIdx)
        {
            return (mResVec.size() > aIdx) ? mResVec[aIdx] : 0;
        }

        virtual T GetConstResourceByaIdx(uint32 aIdx) const
        {
            return (mResVec.size() > aIdx) ? mResVec[aIdx] : 0;
        }

        virtual T GetResource(const std::string& Name)
        {
            TMapResources::iterator it = mResMap.find(Name );
            return (it != mResMap.end()) ? it->second.mPtr : 0;
        }

        virtual T GetConstResource(const std::string& Name) const
        {
            TMapResources::const_iterator it = mResMap.find(Name );
            return (it != mResMap.end()) ? it->second.mPtr : 0;
        }

        virtual bool AddResource( const std::string& Name, T Resource )
        {
            bool lOk = false;

            if (mResMap.find(Name) == mResMap.end() )
            {
                CMapResourceValue lRes(Resource, mResVec.size());
                mResVec.push_back(Resource);
                mResMap[Name] = lRes;
                lOk = true;
            }
            else
            {
                IRIS_LOG_WARNING("Trying to add twice %s", Name.c_str() );
            }

            return lOk;
        }

        virtual void Destroy()
        {
            mResMap.clear();
            mResVec.clear();
        }

        TMapResources &GetResourcesMap()
        {
            return mResMap;
        }

        TVectorResources &GetResourcesVector()
        {
            return mResVec;
        }

        void Clear()
        {
            mResVec.clear();
            mResMap.clear();
        }

        const uint32 GetResourcesCount() const
        {
            //ASSERT( mResMap.size() == mResVec.size(), "map size != vector size" );
            return mResVec.size();
        }
};

#endif
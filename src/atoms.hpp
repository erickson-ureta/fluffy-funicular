#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "atoms.hpp"
#include "constants.hpp"

class GenericAtom
{
    public:
        GenericAtom(const std::string& atomName, size_t size, uint8_t *rawBuffer)
            : _mAtomName(atomName), _mSize(size), _mRawBuffer(rawBuffer)
        {
        }

        const size_t getSize()
        {
            return _mSize;
        }

        const std::string getAtomName()
        {
            return _mAtomName;
        }

        const bool hasChildren()
        {
            return _mHasChildren;
        }

        const size_t getChildrenOffset()
        {
            return _mChildrenOffset;
        }

        virtual void debugPrint() = 0;

    protected:
        // Common fields across all atoms
        uint8_t version;
        // TODO: figure out what to do with the "flags" field later

        // Metadata stuff
        const std::string _mAtomName;
        size_t _mSize;
        bool _mHasChildren = false;
        size_t _mChildrenOffset = 0;
        uint8_t *_mRawBuffer;

        virtual void _parseRawBufIntoFields() = 0;
};

class FtypAtom : public GenericAtom
{
    public:
        FtypAtom(size_t size, uint8_t *rawBuffer)
            : GenericAtom(ATOM_FTYP, size, rawBuffer)
        {
            _parseRawBufIntoFields();
        }

        void debugPrint() override;

    protected:
        uint32_t _mMajorBrand;
        uint32_t _mMinorVersion;
        std::vector<uint32_t> _mCompatibleBrands;

        void _parseRawBufIntoFields() override;
};


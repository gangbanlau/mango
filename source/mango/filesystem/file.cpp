/*
    MANGO Multimedia Development Platform
    Copyright (C) 2012-2018 Twilight Finland 3D Oy Ltd. All rights reserved.
*/
#include <mango/core/string.hpp>
#include <mango/core/exception.hpp>
#include <mango/filesystem/file.hpp>

#define ID "[File] "

namespace mango {
namespace filesystem {

    // -----------------------------------------------------------------
    // File
    // -----------------------------------------------------------------

    File::File(const std::string& s)
    {
        // split s into pathname + filename
        size_t n = s.find_last_of("/\\:");
        std::string filename = s.substr(n + 1);
        std::string filepath = s.substr(0, n + 1);

        // create a temporary path
        Path temp(filepath);

        m_filename = filename;
        m_pathname = temp.pathname();

        AbstractMapper* mapper = temp;
        if (mapper)
        {
            VirtualMemory* vmemory = mapper->mmap(temp.basepath() + m_filename);
            m_memory = UniqueObject<VirtualMemory>(vmemory);
        }
    }

    File::File(const Path& path, const std::string& s)
    {
        // split s into pathname + filename
        size_t n = s.find_last_of("/\\:");
        std::string filename = s.substr(n + 1);
        std::string filepath = s.substr(0, n + 1);

        // create a temporary path
        Path temp(path, filepath);

        m_filename = filename;
        m_pathname = temp.pathname();

        AbstractMapper* mapper = temp;
        if (mapper)
        {
            VirtualMemory* vmemory = mapper->mmap(temp.basepath() + m_filename);
            m_memory = UniqueObject<VirtualMemory>(vmemory);
        }
    }

    File::File(const Memory& memory, const std::string& extension, const std::string& filename)
    {
        std::string password;
        Path path(memory, extension, password);

        // use temporary path's mapper
        m_mapper = path;

        // parse and create mappers
        m_pathname = filename;
        m_filename = parse(m_pathname, "");

        // memory map the file
        if (m_mapper)
        {
            VirtualMemory* vmemory = m_mapper->mmap(m_filename);
            m_memory = UniqueObject<VirtualMemory>(vmemory);
        }
    }

    File::~File()
    {
    }

    const std::string& File::filename() const
    {
        return m_filename;
    }

    File::operator Memory () const
    {
        return getMemory();
    }

	File::operator const u8* () const
	{
        return getMemory().address;
	}

    const u8* File::data() const
    {
        return getMemory().address;
    }

    size_t File::size() const
    {
        return getMemory().size;
    }

    Memory File::getMemory() const
    {
        return m_memory ? *m_memory : Memory(nullptr, 0);
    }

} // namespace filesystem
} // namespace mango

//============================================================================
//
//   SSSS    tt          lll  lll
//  SS  SS   tt           ll   ll
//  SS     tttttt  eeee   ll   ll   aaaa
//   SSSS    tt   ee  ee  ll   ll      aa
//      SS   tt   eeeeee  ll   ll   aaaaa  --  "An Atari 2600 VCS Emulator"
//  SS  SS   tt   ee      ll   ll  aa  aa
//   SSSS     ttt  eeeee llll llll  aaaaa
//
// Copyright (c) 1995-2024 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//============================================================================

#ifndef ELF_LINKER
#define ELF_LINKER

#include "bspf.hxx"
#include "ElfParser.hxx"

class ElfLinker {
  public:
    class ElfLinkError : public std::exception {
      friend ElfLinker;

      public:
        const char* what() const noexcept override { return myReason.c_str(); }

        [[noreturn]] static void raise(string_view message) {
          throw ElfLinkError(message);
        }

      private:
        explicit ElfLinkError(string_view reason) : myReason(reason) {}

      private:
        const string myReason;
    };

    class ElfSymbolResolutionError : public std::exception {
      friend ElfLinker;

      public:
        const char* what() const noexcept override { return myReason.c_str(); }

        [[noreturn]] static void raise(string_view message) {
          throw ElfSymbolResolutionError(message);
        }

      private:
        explicit ElfSymbolResolutionError(string_view reason) : myReason(reason) {}

      private:
        const string myReason;
    };

    enum class SegmentType: uInt8 { text, data };

    struct RelocatedSection {
      SegmentType segment;
      uInt32 offset;
    };

    struct RelocatedSymbol {
      optional<SegmentType> segment;
      uInt32 value;
      bool undefined;
    };

    struct ExternalSymbol {
      string name;
      uInt32 value;
    };

  public:
    ElfLinker(uInt32 textBase, uInt32 dataBase, const ElfParser& parser);

    ElfLinker& setUndefinedSymbolDefault(uInt32 defaultValue);
    void link(const vector<ExternalSymbol>& externalSymbols);

    uInt32 getTextBase() const;
    uInt32 getTextSize() const;
    const uInt8* getTextData() const;

    uInt32 getDataBase() const;
    uInt32 getDataSize() const;
    const uInt8* getDataData() const;

    const vector<uInt32>& getInitArray() const;
    const vector<uInt32>& getPreinitArray() const;

    RelocatedSymbol findRelocatedSymbol(string_view name) const;

    const vector<std::optional<RelocatedSection>>& getRelocatedSections() const;
    const vector<std::optional<RelocatedSymbol>>& getRelocatedSymbols() const;

  private:
    void relocateSections();
    void relocateInitArrays();
    void relocateSymbols(const vector<ExternalSymbol>& externalSymbols);
    void applyRelocationsToSections();
    void copyInitArrays(vector<uInt32>& initArray,  std::unordered_map<uInt32, uInt32> relocatedInitArrays);

    void applyRelocationToSection(const ElfParser::Relocation& relocation, size_t iSection);
    void applyRelocationsToInitArrays(uInt8 initArrayType, vector<uInt32>& initArray,
                                      const std::unordered_map<uInt32, uInt32>& relocatedInitArrays);

    uInt32 read32(const uInt8* address);
    void write32(uInt8* address, uInt32 value);

  private:
    std::optional<uInt32> undefinedSymbolDefault;

    const uInt32 myTextBase{0};
    const uInt32 myDataBase{0};
    const ElfParser& myParser;

    uInt32 myTextSize{0};
    uInt32 myDataSize{0};
    unique_ptr<uInt8[]> myTextData;
    unique_ptr<uInt8[]> myDataData;

    vector<optional<RelocatedSection>> myRelocatedSections;
    vector<optional<RelocatedSymbol>> myRelocatedSymbols;

    vector<uInt32> myInitArray;
    vector<uInt32> myPreinitArray;

  private:
    ElfLinker(const ElfLinker&) = delete;
    ElfLinker(ElfLinker&&) = delete;
    ElfLinker& operator=(const ElfLinker&) = delete;
    ElfLinker& operator=(ElfLinker&&) = delete;
};

#endif // ELF_LINKER

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

#ifndef CARTRIDGE_ELF
#define CARTRIDGE_ELF

#include "bspf.hxx"
#include "Cart.hxx"

class CartridgeELF: public Cartridge {
  public:
    CartridgeELF(const ByteBuffer& image, size_t size, string_view md5,
                 const Settings& settings);
    virtual ~CartridgeELF();

  // Methods from Device
  public:
    void reset() override;

    void install(System& system) override;

    bool save(Serializer& out) const override;

    bool load(Serializer& in) override;

    uInt8 peek(uInt16 address) override;

    bool poke(uInt16 address, uInt8 value) override;

  // Methods from Cartridge
  public:
    bool bankChanged() override { return false; }

    bool patch(uInt16 address, uInt8 value) override { return false; }

    const ByteBuffer& getImage(size_t& size) const override;

    string name() const override { return "CartridgeELF"; };

  private:
    struct ScheduledRead {
      uInt16 address;
      uInt8 value;
    };

    class ReadStream {
      public:
        ReadStream();

        void Reset();

        void Push(uInt8 value);
        void Push(uInt8 value, uInt8 address);

        bool HasPendingRead() const;
        uInt16 GetNextReadAddress() const;
        uInt8 Pop(uInt16 readAddress);

      private:
        unique_ptr<ScheduledRead[]> myStream;
        size_t myStreamNext{0};
        size_t myStreamSize{0};

        uInt16 myNextReadAddress{0};
    };

  private:
    ByteBuffer myImage;
    size_t myImageSize{0};

    System* mySystem{nullptr};

    ReadStream myReadStream;
};

#endif // CARTRIDGE_ELF

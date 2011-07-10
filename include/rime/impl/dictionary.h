// vim: set sts=2 sw=2 et:
// encoding: utf-8
//
// Copyleft 2011 RIME Developers
// License: GPLv3
//
// 2011-07-05 GONG Chen <chen.sst@gmail.com>
//
#ifndef RIME_DICTIONARY_H_
#define RIME_DICTIONRAY_H_

#include <list>
#include <string>
#include <vector>
#include <rime/common.h>
#include <rime/impl/prism.h>
#include <rime/impl/table.h>
#include <rime/impl/vocabulary.h>

namespace rime {

class RawCode : public std::vector<std::string> {
 public:
  const std::string ToString() const;
  void FromString(const std::string &str_code);
};

typedef std::list<std::pair<Code, table::EntryIterator> > DictEntryCollector;

class DictEntryIterator {
 public:
  DictEntryIterator();
  operator bool() const;
  shared_ptr<DictEntry> operator->();
  DictEntryIterator& operator++();
  void AddChunk(const Code &code, const table::EntryIterator &table_entry_iter);
 private:
  DictEntryCollector chunks_;
  shared_ptr<DictEntry> entry_;
};

class Dictionary {
 public:
  Dictionary(const std::string &name);
  virtual ~Dictionary();

  bool Compile(const std::string &source_file);
  bool Load();
  bool Unload();
  
  DictEntryIterator Lookup(const std::string &str_code);
  bool Decode(const Code &code, RawCode *result);

  bool loaded() const { return loaded_; }
  
 private:
  std::string name_;
  bool loaded_;
  scoped_ptr<Prism> prism_;
  scoped_ptr<Table> table_;
};

}  // namespace rime

#endif  // RIME_DICTIONRAY_H_
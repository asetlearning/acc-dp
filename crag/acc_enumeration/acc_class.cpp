//
// Created by dpantele on 5/23/16.
//

#include <fmt/format.h>

#include "acc_class.h"
#include "acc_classes.h"
#include "state_dump.h"


void ACClass::DescribeForLog(std::ostream* out) const {
  *out << id_ << ": " << initial_ << "(";
  switch(init_kind()) {
    case AutKind::Ident:
      *out << "Id";
      break;
    case AutKind::x_xy:
      *out << "x->xy";
      break;
    case AutKind::x_y:
      *out << "x<->y";
      break;
    case AutKind::y_Y:
      *out << "y->Y";
      break;
  }
  *out << "): ";
  if (merged_with_ != id_) {
    *out << "=> " << merged_with_;
  } else {
    *out << minimal_ << ", " << aut_types_;
  }
}

void ACClass::DescribeForLog(fmt::memory_buffer *out) const {
  fmt::format_to(std::back_inserter(*out), "{}: {}(", id_, initial_.toString());
  switch (init_kind()) {
    case AutKind::Ident:
      fmt::format_to(std::back_inserter(*out), "Id");
      break;
    case AutKind::x_xy:
      fmt::format_to(std::back_inserter(*out), "x->xy");
      break;
    case AutKind::x_y:
      fmt::format_to(std::back_inserter(*out), "x<->y");
      break;
    case AutKind::y_Y:
      fmt::format_to(std::back_inserter(*out), "y->Y");
      break;
  }


  if (id_ != merged_with_) {
    fmt::format_to(std::back_inserter(*out), "): => ", merged_with_);
  } else {
    fmt::format_to(std::back_inserter(*out), "): {}, {}", minimal_.toString(), aut_types_.to_string());
  }
}

ACClass::ACClass(size_t id, ACPair initial, ACPair image, AutKind kind, ACStateDump* logger)
  : initial_(std::move(initial))
  , aut_types_(1u)
  , minimal_(crag::ConjugationInverseFlipNormalForm(image))
  , merged_with_(id)
  , id_(id)
  , logger_(logger)
{
  assert(kind == init_kind());
  logger_->DumpPairClass(minimal_, *this);
  logger_->NewMinimum(*this, minimal_);
}
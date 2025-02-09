#!/bin/bash

SCRIPTDIR=$(dirname "${BASH_SOURCE[0]}")
OUTDIR=$(realpath "$SCRIPTDIR")

SRCDIRS=$(realpath "$SCRIPTDIR/..")/ $(realpath "$SCRIPTDIR/../..")/

OPTS="-tr-function-alias QT_TRANSLATE_NOOP+=TRANSLATE,QT_TRANSLATE_NOOP+=TRANSLATE_SV,QT_TRANSLATE_NOOP+=TRANSLATE_STR,QT_TRANSLATE_NOOP+=TRANSLATE_FS,QT_TRANSLATE_N_NOOP3+=TRANSLATE_FMT,QT_TRANSLATE_NOOP+=TRANSLATE_NOOP,translate+=TRANSLATE_PLURAL_STR,translate+=TRANSLATE_PLURAL_FS"

find "$OUTDIR" -name "*.ts" | while read -r TS_FILE; do
  lupdate $SRCDIRS $OPTS -locations none -source-language en -ts "$TS_FILE"
done

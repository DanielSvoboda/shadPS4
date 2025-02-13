#!/bin/bash

SCRIPTDIR=$(dirname "${BASH_SOURCE[0]}")

OPTS="-tr-function-alias QT_TRANSLATE_NOOP+=TRANSLATE,QT_TRANSLATE_NOOP+=TRANSLATE_SV,QT_TRANSLATE_NOOP+=TRANSLATE_STR,QT_TRANSLATE_NOOP+=TRANSLATE_FS,QT_TRANSLATE_N_NOOP3+=TRANSLATE_FMT,QT_TRANSLATE_NOOP+=TRANSLATE_NOOP,translate+=TRANSLATE_PLURAL_STR,translate+=TRANSLATE_PLURAL_FS -no-obsolete"
SRCDIRS=$(realpath "$SCRIPTDIR/..") $(realpath "$SCRIPTDIR/../..")
OUTDIR=$(realpath "$SCRIPTDIR")

# Gerar o arquivo .ts com lupdate
lupdate $SRCDIRS $OPTS -locations none -source-language en -ts "$OUTDIR/en_US.ts"

# Formatar o arquivo .ts com xmllint
xmllint --format "$OUTDIR/en_US.ts" -o "$OUTDIR/en_US.ts"

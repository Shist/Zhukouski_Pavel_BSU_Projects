package model.text_unit.text;

/**
 *
 * @author Zhukouski Pavel
 *
 */
public enum TextUnitTypeEnum {
    WORD {
        @Override
        public String toString() {
            return "word";
        }
    },
    PUNCTUATION_MARK {
        @Override
        public String toString() {
            return "punctuation mark";
        }
    },
    SENTENCE {
        @Override
        public String toString() {
            return "sentence";
        }
    },
    CODE_LINE {
        @Override
        public String toString() {
            return "code line";
        }
    },
    PARAGRAPH {
        @Override
        public String toString() {
            return "paragraph";
        }
    },
    CODE_BLOCK {
        @Override
        public String toString() {
            return "code block";
        }
    },
    TEXT {
        @Override
        public String toString() {
            return "text";
        }
    }

}

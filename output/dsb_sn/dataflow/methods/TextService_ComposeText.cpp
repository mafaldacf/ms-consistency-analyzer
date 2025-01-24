[0] (PointerObject PointerType) t (*socialnetwork.TextServiceImpl struct{urlShortenService socialnetwork.UrlShortenService, userMentionService socialnetwork.UserMentionService})
[_1] (StructObject UserType) socialnetwork.TextServiceImpl struct{urlShortenService socialnetwork.UrlShortenService, userMentionService socialnetwork.UserMentionService}
[__2] (FieldObject FieldType) urlShortenService socialnetwork.UrlShortenService
[___3] (ServiceObject ServiceType) urlShortenService socialnetwork.UrlShortenService
[__2] (FieldObject FieldType) userMentionService socialnetwork.UserMentionService
[___3] (ServiceObject ServiceType) userMentionService socialnetwork.UserMentionService

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ ComposePostService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (BasicObject BasicType) text string
[_1] (Reference BasicType) ref <text string> @ ComposePostService
[__2] (Reference BasicType) ref <text string> @ Wrk2APIService

[0] (PointerObject PointerType) r (*regexp.Regexp struct{expr string, prog (*syntax.Prog struct{Inst []syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Start int, NumCap int}), onepass (*regexp.onePassProg struct{Inst []regexp.onePassInst struct{Inst syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Next []uint32}, Start int, NumCap int}), numSubexp int, maxBitStateLen int, subexpNames []string, prefix string, prefixBytes []byte, prefixRune rune, prefixEnd uint32, mpool int, matchcap int, prefixComplete bool, cond syntax.EmptyOp uint8, minInputLen int, longest bool})
[_1] (BasicObject BasicType) `@[a-zA-Z0-9-_]+` string
[_1] (BasicObject BasicType) `@[a-zA-Z0-9-_]+` string
[_1] (StructObject UserType) regexp.Regexp struct{expr string, prog (*syntax.Prog struct{Inst []syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Start int, NumCap int}), onepass (*regexp.onePassProg struct{Inst []regexp.onePassInst struct{Inst syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Next []uint32}, Start int, NumCap int}), numSubexp int, maxBitStateLen int, subexpNames []string, prefix string, prefixBytes []byte, prefixRune rune, prefixEnd uint32, mpool int, matchcap int, prefixComplete bool, cond syntax.EmptyOp uint8, minInputLen int, longest bool}

[0] (SliceObject SliceType) matches []string
[_1] (BasicObject BasicType) text string
[__2] (Reference BasicType) ref <text string> @ ComposePostService
[___3] (Reference BasicType) ref <text string> @ Wrk2APIService
[_1] (BasicObject BasicType) int
[_1] (BasicObject BasicType) text string
[__2] (Reference BasicType) ref <text string> @ ComposePostService
[___3] (Reference BasicType) ref <text string> @ Wrk2APIService
[_1] (BasicObject BasicType) int

[0] (ArrayObject ArrayType) usernames []string
[_1] (BasicObject BasicType) m string

[0] (BasicObject BasicType) m string

[0] (ArrayObject ArrayType) usernames []string
[_1] (BasicObject BasicType) m string

[0] (PointerObject PointerType) t (*socialnetwork.TextServiceImpl struct{urlShortenService socialnetwork.UrlShortenService, userMentionService socialnetwork.UserMentionService})
[_1] (StructObject UserType) socialnetwork.TextServiceImpl struct{urlShortenService socialnetwork.UrlShortenService, userMentionService socialnetwork.UserMentionService}
[__2] (FieldObject FieldType) urlShortenService socialnetwork.UrlShortenService
[___3] (ServiceObject ServiceType) urlShortenService socialnetwork.UrlShortenService
[__2] (FieldObject FieldType) userMentionService socialnetwork.UserMentionService
[___3] (ServiceObject ServiceType) userMentionService socialnetwork.UserMentionService

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ ComposePostService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (BasicObject BasicType) text string
[_1] (Reference BasicType) ref <text string> @ ComposePostService
[__2] (Reference BasicType) ref <text string> @ Wrk2APIService

[0] (PointerObject PointerType) r (*regexp.Regexp struct{expr string, prog (*syntax.Prog struct{Inst []syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Start int, NumCap int}), onepass (*regexp.onePassProg struct{Inst []regexp.onePassInst struct{Inst syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Next []uint32}, Start int, NumCap int}), numSubexp int, maxBitStateLen int, subexpNames []string, prefix string, prefixBytes []byte, prefixRune rune, prefixEnd uint32, mpool int, matchcap int, prefixComplete bool, cond syntax.EmptyOp uint8, minInputLen int, longest bool})
[_1] (BasicObject BasicType) `@[a-zA-Z0-9-_]+` string
[_1] (BasicObject BasicType) `@[a-zA-Z0-9-_]+` string
[_1] (StructObject UserType) regexp.Regexp struct{expr string, prog (*syntax.Prog struct{Inst []syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Start int, NumCap int}), onepass (*regexp.onePassProg struct{Inst []regexp.onePassInst struct{Inst syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Next []uint32}, Start int, NumCap int}), numSubexp int, maxBitStateLen int, subexpNames []string, prefix string, prefixBytes []byte, prefixRune rune, prefixEnd uint32, mpool int, matchcap int, prefixComplete bool, cond syntax.EmptyOp uint8, minInputLen int, longest bool}

[0] (SliceObject SliceType) matches []string
[_1] (BasicObject BasicType) text string
[__2] (Reference BasicType) ref <text string> @ ComposePostService
[___3] (Reference BasicType) ref <text string> @ Wrk2APIService
[_1] (BasicObject BasicType) int
[_1] (BasicObject BasicType) text string
[__2] (Reference BasicType) ref <text string> @ ComposePostService
[___3] (Reference BasicType) ref <text string> @ Wrk2APIService
[_1] (BasicObject BasicType) int

[0] (ArrayObject ArrayType) usernames []string
[_1] (BasicObject BasicType) m string

[0] (BasicObject BasicType) m string

[0] (PointerObject PointerType) url_re (*regexp.Regexp struct{expr string, prog (*syntax.Prog struct{Inst []syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Start int, NumCap int}), onepass (*regexp.onePassProg struct{Inst []regexp.onePassInst struct{Inst syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Next []uint32}, Start int, NumCap int}), numSubexp int, maxBitStateLen int, subexpNames []string, prefix string, prefixBytes []byte, prefixRune rune, prefixEnd uint32, mpool int, matchcap int, prefixComplete bool, cond syntax.EmptyOp uint8, minInputLen int, longest bool})
[_1] (BasicObject BasicType) `(http://|https://)([a-zA-Z0-9_!~*'().&=+$%-]+)` string
[_1] (BasicObject BasicType) `(http://|https://)([a-zA-Z0-9_!~*'().&=+$%-]+)` string
[_1] (StructObject UserType) regexp.Regexp struct{expr string, prog (*syntax.Prog struct{Inst []syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Start int, NumCap int}), onepass (*regexp.onePassProg struct{Inst []regexp.onePassInst struct{Inst syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Next []uint32}, Start int, NumCap int}), numSubexp int, maxBitStateLen int, subexpNames []string, prefix string, prefixBytes []byte, prefixRune rune, prefixEnd uint32, mpool int, matchcap int, prefixComplete bool, cond syntax.EmptyOp uint8, minInputLen int, longest bool}

[0] (SliceObject SliceType) url_strings []string
[_1] (BasicObject BasicType) text string
[__2] (Reference BasicType) ref <text string> @ ComposePostService
[___3] (Reference BasicType) ref <text string> @ Wrk2APIService
[_1] (BasicObject BasicType) int
[_1] (BasicObject BasicType) text string
[__2] (Reference BasicType) ref <text string> @ ComposePostService
[___3] (Reference BasicType) ref <text string> @ Wrk2APIService
[_1] (BasicObject BasicType) int

[0] (BasicObject BasicType) err1 error

[0] (BasicObject BasicType) err2 error

[0] (ArrayObject ArrayType) urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}

[0] (ArrayObject ArrayType) user_mentions []socialnetwork.UserMention struct{UserID int64, Username string}

[0] (StructObject UserType) wg sync.WaitGroup

[0] (BasicObject BasicType) updated_text string

[0] (BasicObject BasicType) idx string

[0] (BasicObject BasicType) url_string 0 int

[0] (BasicObject BasicType) updated_text string
[_1] (BasicObject BasicType) updated_text string
[_1] (BasicObject BasicType) url_string 0 int
[_1] (BasicObject BasicType) ShortenedUrl string
[_1] (BasicObject BasicType) updated_text string
[_1] (BasicObject BasicType) url_string 0 int
[_1] (BasicObject BasicType) ShortenedUrl string

[0] (PointerObject PointerType) t (*socialnetwork.TextServiceImpl struct{urlShortenService socialnetwork.UrlShortenService, userMentionService socialnetwork.UserMentionService})
[_1] (StructObject UserType) socialnetwork.TextServiceImpl struct{urlShortenService socialnetwork.UrlShortenService, userMentionService socialnetwork.UserMentionService}
[__2] (FieldObject FieldType) urlShortenService socialnetwork.UrlShortenService
[___3] (ServiceObject ServiceType) urlShortenService socialnetwork.UrlShortenService
[__2] (FieldObject FieldType) userMentionService socialnetwork.UserMentionService
[___3] (ServiceObject ServiceType) userMentionService socialnetwork.UserMentionService

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ ComposePostService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (BasicObject BasicType) text string
[_1] (Reference BasicType) ref <text string> @ ComposePostService
[__2] (Reference BasicType) ref <text string> @ Wrk2APIService

[0] (PointerObject PointerType) r (*regexp.Regexp struct{expr string, prog (*syntax.Prog struct{Inst []syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Start int, NumCap int}), onepass (*regexp.onePassProg struct{Inst []regexp.onePassInst struct{Inst syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Next []uint32}, Start int, NumCap int}), numSubexp int, maxBitStateLen int, subexpNames []string, prefix string, prefixBytes []byte, prefixRune rune, prefixEnd uint32, mpool int, matchcap int, prefixComplete bool, cond syntax.EmptyOp uint8, minInputLen int, longest bool})
[_1] (BasicObject BasicType) `@[a-zA-Z0-9-_]+` string
[_1] (BasicObject BasicType) `@[a-zA-Z0-9-_]+` string
[_1] (StructObject UserType) regexp.Regexp struct{expr string, prog (*syntax.Prog struct{Inst []syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Start int, NumCap int}), onepass (*regexp.onePassProg struct{Inst []regexp.onePassInst struct{Inst syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Next []uint32}, Start int, NumCap int}), numSubexp int, maxBitStateLen int, subexpNames []string, prefix string, prefixBytes []byte, prefixRune rune, prefixEnd uint32, mpool int, matchcap int, prefixComplete bool, cond syntax.EmptyOp uint8, minInputLen int, longest bool}

[0] (SliceObject SliceType) matches []string
[_1] (BasicObject BasicType) text string
[__2] (Reference BasicType) ref <text string> @ ComposePostService
[___3] (Reference BasicType) ref <text string> @ Wrk2APIService
[_1] (BasicObject BasicType) int
[_1] (BasicObject BasicType) text string
[__2] (Reference BasicType) ref <text string> @ ComposePostService
[___3] (Reference BasicType) ref <text string> @ Wrk2APIService
[_1] (BasicObject BasicType) int

[0] (ArrayObject ArrayType) usernames []string
[_1] (BasicObject BasicType) m string

[0] (BasicObject BasicType) m string

[0] (ArrayObject ArrayType) usernames []string
[_1] (BasicObject BasicType) m string

[0] (PointerObject PointerType) t (*socialnetwork.TextServiceImpl struct{urlShortenService socialnetwork.UrlShortenService, userMentionService socialnetwork.UserMentionService})
[_1] (StructObject UserType) socialnetwork.TextServiceImpl struct{urlShortenService socialnetwork.UrlShortenService, userMentionService socialnetwork.UserMentionService}
[__2] (FieldObject FieldType) urlShortenService socialnetwork.UrlShortenService
[___3] (ServiceObject ServiceType) urlShortenService socialnetwork.UrlShortenService
[__2] (FieldObject FieldType) userMentionService socialnetwork.UserMentionService
[___3] (ServiceObject ServiceType) userMentionService socialnetwork.UserMentionService

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ ComposePostService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (BasicObject BasicType) text string
[_1] (Reference BasicType) ref <text string> @ ComposePostService
[__2] (Reference BasicType) ref <text string> @ Wrk2APIService

[0] (PointerObject PointerType) r (*regexp.Regexp struct{expr string, prog (*syntax.Prog struct{Inst []syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Start int, NumCap int}), onepass (*regexp.onePassProg struct{Inst []regexp.onePassInst struct{Inst syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Next []uint32}, Start int, NumCap int}), numSubexp int, maxBitStateLen int, subexpNames []string, prefix string, prefixBytes []byte, prefixRune rune, prefixEnd uint32, mpool int, matchcap int, prefixComplete bool, cond syntax.EmptyOp uint8, minInputLen int, longest bool})
[_1] (BasicObject BasicType) `@[a-zA-Z0-9-_]+` string
[_1] (BasicObject BasicType) `@[a-zA-Z0-9-_]+` string
[_1] (StructObject UserType) regexp.Regexp struct{expr string, prog (*syntax.Prog struct{Inst []syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Start int, NumCap int}), onepass (*regexp.onePassProg struct{Inst []regexp.onePassInst struct{Inst syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Next []uint32}, Start int, NumCap int}), numSubexp int, maxBitStateLen int, subexpNames []string, prefix string, prefixBytes []byte, prefixRune rune, prefixEnd uint32, mpool int, matchcap int, prefixComplete bool, cond syntax.EmptyOp uint8, minInputLen int, longest bool}

[0] (SliceObject SliceType) matches []string
[_1] (BasicObject BasicType) text string
[__2] (Reference BasicType) ref <text string> @ ComposePostService
[___3] (Reference BasicType) ref <text string> @ Wrk2APIService
[_1] (BasicObject BasicType) int
[_1] (BasicObject BasicType) text string
[__2] (Reference BasicType) ref <text string> @ ComposePostService
[___3] (Reference BasicType) ref <text string> @ Wrk2APIService
[_1] (BasicObject BasicType) int

[0] (ArrayObject ArrayType) usernames []string
[_1] (BasicObject BasicType) m string

[0] (BasicObject BasicType) m string

[0] (PointerObject PointerType) url_re (*regexp.Regexp struct{expr string, prog (*syntax.Prog struct{Inst []syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Start int, NumCap int}), onepass (*regexp.onePassProg struct{Inst []regexp.onePassInst struct{Inst syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Next []uint32}, Start int, NumCap int}), numSubexp int, maxBitStateLen int, subexpNames []string, prefix string, prefixBytes []byte, prefixRune rune, prefixEnd uint32, mpool int, matchcap int, prefixComplete bool, cond syntax.EmptyOp uint8, minInputLen int, longest bool})
[_1] (BasicObject BasicType) `(http://|https://)([a-zA-Z0-9_!~*'().&=+$%-]+)` string
[_1] (BasicObject BasicType) `(http://|https://)([a-zA-Z0-9_!~*'().&=+$%-]+)` string
[_1] (StructObject UserType) regexp.Regexp struct{expr string, prog (*syntax.Prog struct{Inst []syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Start int, NumCap int}), onepass (*regexp.onePassProg struct{Inst []regexp.onePassInst struct{Inst syntax.Inst struct{Op syntax.InstOp uint8, Out uint32, Arg uint32, Rune []rune}, Next []uint32}, Start int, NumCap int}), numSubexp int, maxBitStateLen int, subexpNames []string, prefix string, prefixBytes []byte, prefixRune rune, prefixEnd uint32, mpool int, matchcap int, prefixComplete bool, cond syntax.EmptyOp uint8, minInputLen int, longest bool}

[0] (SliceObject SliceType) url_strings []string
[_1] (BasicObject BasicType) text string
[__2] (Reference BasicType) ref <text string> @ ComposePostService
[___3] (Reference BasicType) ref <text string> @ Wrk2APIService
[_1] (BasicObject BasicType) int
[_1] (BasicObject BasicType) text string
[__2] (Reference BasicType) ref <text string> @ ComposePostService
[___3] (Reference BasicType) ref <text string> @ Wrk2APIService
[_1] (BasicObject BasicType) int

[0] (BasicObject BasicType) err1 error

[0] (BasicObject BasicType) err2 error

[0] (ArrayObject ArrayType) urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}

[0] (ArrayObject ArrayType) user_mentions []socialnetwork.UserMention struct{UserID int64, Username string}

[0] (StructObject UserType) wg sync.WaitGroup

[0] (BasicObject BasicType) updated_text string

[0] (BasicObject BasicType) idx string

[0] (BasicObject BasicType) url_string 0 int


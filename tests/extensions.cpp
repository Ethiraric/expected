#include <catch2/catch.hpp>
#include <tl/expected.hpp>

#define TOKENPASTE(x, y) x##y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)
#define STATIC_REQUIRE(e)                                                      \
  constexpr bool TOKENPASTE2(rqure, __LINE__) = e;                             \
  REQUIRE(e);

TEST_CASE("Map extensions", "[extensions.map]") {
  auto mul2 = [](int a) { return a * 2; };
  auto ret_void = [](int a) {};

  {
    tl::expected<int, int> e = 21;
    auto ret = e.map(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.map(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).map(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).map(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = e.map(ret_void);
    REQUIRE(ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.map(ret_void);
    REQUIRE(ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).map(ret_void);
    REQUIRE(ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).map(ret_void);
    REQUIRE(ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map(ret_void);
    REQUIRE(!ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map(ret_void);
    REQUIRE(!ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map(ret_void);
    REQUIRE(!ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map(ret_void);
    REQUIRE(!ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }


  // mapping functions which return references
  {
    tl::expected<int, int> e(42);
    auto ret = e.map([](int& i) -> int& { return i; });
    REQUIRE(ret);
    REQUIRE(ret == 42);
  }
}

TEST_CASE("Map error extensions", "[extensions.map_error]") {
  auto mul2 = [](int a) { return a * 2; };
  auto ret_void = [](int a) {};

  {
    tl::expected<int, int> e = 21;
    auto ret = e.map_error(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.map_error(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).map_error(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).map_error(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map_error(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 42);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map_error(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 42);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map_error(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 42);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map_error(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 42);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = e.map_error(ret_void);
    REQUIRE(ret);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.map_error(ret_void);
    REQUIRE(ret);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).map_error(ret_void);
    REQUIRE(ret);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).map_error(ret_void);
    REQUIRE(ret);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map_error(ret_void);
    REQUIRE(!ret);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map_error(ret_void);
    REQUIRE(!ret);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map_error(ret_void);
    REQUIRE(!ret);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map_error(ret_void);
    REQUIRE(!ret);
  }

}

TEST_CASE("And then extensions", "[extensions.and_then]") {
  auto succeed = [](int a) { return tl::expected<int, int>(21 * 2); };
  auto fail = [](int a) { return tl::expected<int, int>(tl::unexpect, 17); };

  {
    tl::expected<int, int> e = 21;
    auto ret = e.and_then(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.and_then(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).and_then(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).and_then(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = e.and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.and_then(succeed);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.and_then(succeed);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).and_then(succeed);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).and_then(succeed);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }
}

TEST_CASE("or_else", "[extensions.or_else]") {
  using eptr = std::unique_ptr<int>;
  auto succeed = [](int a) { return tl::expected<int, int>(21 * 2); };
  auto succeedptr = [](eptr e) { return tl::expected<int,eptr>(21*2);};
  auto fail =    [](int a) { return tl::expected<int,int>(tl::unexpect, 17);};
  auto efail =   [](eptr e) { *e = 17;return tl::expected<int,eptr>(tl::unexpect, std::move(e));};
  auto failptr = [](eptr e) { return tl::expected<int,eptr>(tl::unexpect, std::move(e));};
  auto failvoid = [](int) {};
  auto failvoidptr = [](const eptr&) { /* don't consume */};
  auto consumeptr = [](eptr) {};
  auto make_u_int = [](int n) { return std::unique_ptr<int>(new int(n));};

  {
    tl::expected<int, int> e = 21;
    auto ret = e.or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, eptr> e = 21;
    auto ret = std::move(e).or_else(succeedptr);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = e.or_else(fail);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.or_else(fail);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).or_else(fail);
    REQUIRE(ret);
    REQUIRE(ret == 21);
  }


  {
    tl::expected<int, eptr> e = 21;
    auto ret = std::move(e).or_else(efail);
    REQUIRE(ret);
    REQUIRE(ret == 21);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).or_else(fail);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    tl::expected<int, eptr> e(tl::unexpect, make_u_int(21));
    auto ret = std::move(e).or_else(succeedptr);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.or_else(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.or_else(failvoid);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.or_else(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.or_else(failvoid);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).or_else(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).or_else(failvoid);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, eptr> e(tl::unexpect, make_u_int(21));
    auto ret = std::move(e).or_else(failvoidptr);
    REQUIRE(!ret);
    REQUIRE(*ret.error() == 21);
  }

  {
    tl::expected<int, eptr> e(tl::unexpect, make_u_int(21));
    auto ret = std::move(e).or_else(consumeptr);
    REQUIRE(!ret);
    REQUIRE(ret.error() == nullptr);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).or_else(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).or_else(failvoid);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

}

TEST_CASE("And then with extensions", "[extensions.and_then_with]") {
  auto succeed = [](char const* a, int b) { return tl::expected<int, int>(21 * 2); };
  auto fail = [](char const* a, int b) { return tl::expected<int, int>(tl::unexpect, 17); };

  {
    tl::expected<int, int> e = 21;
    auto ret = e.and_then_with(succeed, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.and_then_with(succeed, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).and_then_with(succeed, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).and_then_with(succeed, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = e.and_then_with(fail, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.and_then_with(fail, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).and_then_with(fail, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).and_then_with(fail, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.and_then_with(succeed, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.and_then_with(succeed, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).and_then_with(succeed, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).and_then_with(succeed, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.and_then_with(fail, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.and_then_with(fail, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).and_then_with(fail, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).and_then_with(fail, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }
}

TEST_CASE("Map with extensions", "[extensions.map_with]") {
  auto mul2 = [](char const* a, int b) { return b * 2; };
  auto ret_void = [](char const* a,int b) {};

  struct S { int f(int i) { return 3; } };
  {
    tl::expected<int, int> e = 21;
    auto ret = e.map_with(mul2, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 42);
    S s;
    auto x = ret.map_with(&S::f, &s);
    REQUIRE(x == 3);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.map_with(mul2, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).map_with(mul2, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).map_with(mul2, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map_with(mul2, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map_with(mul2, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map_with(mul2, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map_with(mul2, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = e.map_with(ret_void, "foo");
    REQUIRE(ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.map_with(ret_void, "foo");
    REQUIRE(ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).map_with(ret_void, "foo");
    REQUIRE(ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).map_with(ret_void, "foo");
    REQUIRE(ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map_with(ret_void, "foo");
    REQUIRE(!ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map_with(ret_void, "foo");
    REQUIRE(!ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map_with(ret_void, "foo");
    REQUIRE(!ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map_with(ret_void, "foo");
    REQUIRE(!ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }


  // map_withping functions which return references
  {
    tl::expected<int, int> e(42);
    auto ret = e.map_with([](int& i) -> int& { return i; });
    REQUIRE(ret);
    REQUIRE(ret == 42);
  }
}

TEST_CASE("Map error with extensions", "[extensions.map_error_with]") {
  auto mul2 = [](char const *a, int b) { return b * 2; };
  auto ret_void = [](char const *a, int b) {};

  {
    tl::expected<int, int> e = 21;
    auto ret = e.map_error_with(mul2, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.map_error_with(mul2, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).map_error_with(mul2, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).map_error_with(mul2, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map_error_with(mul2, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 42);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map_error_with(mul2, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 42);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map_error_with(mul2, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 42);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map_error_with(mul2, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 42);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = e.map_error_with(ret_void, "foo");
    REQUIRE(ret);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.map_error_with(ret_void, "foo");
    REQUIRE(ret);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).map_error_with(ret_void, "foo");
    REQUIRE(ret);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).map_error_with(ret_void, "foo");
    REQUIRE(ret);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map_error_with(ret_void, "foo");
    REQUIRE(!ret);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map_error_with(ret_void, "foo");
    REQUIRE(!ret);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map_error_with(ret_void, "foo");
    REQUIRE(!ret);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map_error_with(ret_void, "foo");
    REQUIRE(!ret);
  }
}

TEST_CASE("or_else_with", "[extensions.or_else_with]") {
  using eptr = std::unique_ptr<int>;
  auto succeed = [](char const* f, int a) { return tl::expected<int, int>(21 * 2); };
  auto succeedptr = [](char const* f, eptr e) { return tl::expected<int,eptr>(21*2);};
  auto fail =    [](char const* f, int a) { return tl::expected<int,int>(tl::unexpect, 17);};
  auto efail =   [](char const* f, eptr e) { *e = 17;return tl::expected<int,eptr>(tl::unexpect, std::move(e));};
  auto failptr = [](char const* f, eptr e) { return tl::expected<int,eptr>(tl::unexpect, std::move(e));};
  auto failvoid = [](char const* f, int) {};
  auto failvoidptr = [](char const* f, const eptr&) { /* don't consume */};
  auto consumeptr = [](char const* f, eptr) {};
  auto make_u_int = [](int n) { return std::unique_ptr<int>(new int(n));};

  {
    tl::expected<int, int> e = 21;
    auto ret = e.or_else_with(succeed, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.or_else_with(succeed, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).or_else_with(succeed, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, eptr> e = 21;
    auto ret = std::move(e).or_else_with(succeedptr, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).or_else_with(succeed, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = e.or_else_with(fail, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.or_else_with(fail, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).or_else_with(fail, "foo");
    REQUIRE(ret);
    REQUIRE(ret == 21);
  }


  {
    tl::expected<int, eptr> e = 21;
    auto ret = std::move(e).or_else_with(efail, "foo");
    REQUIRE(ret);
    REQUIRE(ret == 21);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).or_else_with(fail, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.or_else_with(succeed, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.or_else_with(succeed, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).or_else_with(succeed, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    tl::expected<int, eptr> e(tl::unexpect, make_u_int(21));
    auto ret = std::move(e).or_else_with(succeedptr, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).or_else_with(succeed, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.or_else_with(fail, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.or_else_with(failvoid, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.or_else_with(fail, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.or_else_with(failvoid, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).or_else_with(fail, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).or_else_with(failvoid, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, eptr> e(tl::unexpect, make_u_int(21));
    auto ret = std::move(e).or_else_with(failvoidptr, "foo");
    REQUIRE(!ret);
    REQUIRE(*ret.error() == 21);
  }

  {
    tl::expected<int, eptr> e(tl::unexpect, make_u_int(21));
    auto ret = std::move(e).or_else_with(consumeptr, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == nullptr);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).or_else_with(fail, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).or_else_with(failvoid, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }
}

TEST_CASE("Pass Through extensions", "[extensions.pass_through]") {
  auto ret_void = [](char const* a, int b) {};
  auto ret_void_add_one = [](char const* a, int& b) { ++b; };

  {
    tl::expected<int, int> e = 21;
    auto ret = e.pass_through(ret_void, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = e.pass_through(ret_void_add_one, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 22);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.pass_through(ret_void, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).pass_through(ret_void, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).pass_through(ret_void, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.pass_through(ret_void, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.pass_through(ret_void, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).pass_through(ret_void, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).pass_through(ret_void, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }


  // map_withping functions which return references
  {
    tl::expected<int, int> e(42);
    auto ret = e.map_with([](int& i) -> int& { return i; });
    REQUIRE(ret);
    REQUIRE(ret == 42);
  }
}

TEST_CASE("Pass error through extensions", "[extensions.pass_error_through]") {
  auto ret_void = [](char const *a, int& b) { b += 2;};
  auto ret_void_const = [](char const *a, int const& b) { };

  {
    tl::expected<int, int> e = 21;
    auto ret = e.pass_error_through(ret_void, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.pass_error_through(ret_void_const, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).pass_error_through(ret_void, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).pass_error_through(ret_void_const, "foo");
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.pass_error_through(ret_void, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 23);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.pass_error_through(ret_void_const, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).pass_error_through(ret_void, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 23);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).pass_error_through(ret_void_const, "foo");
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = e.pass_error_through(ret_void, "foo");
    REQUIRE(ret);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.pass_error_through(ret_void_const, "foo");
    REQUIRE(ret);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).pass_error_through(ret_void, "foo");
    REQUIRE(ret);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).pass_error_through(ret_void_const, "foo");
    REQUIRE(ret);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.pass_error_through(ret_void, "foo");
    REQUIRE(!ret);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.pass_error_through(ret_void_const, "foo");
    REQUIRE(!ret);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).pass_error_through(ret_void, "foo");
    REQUIRE(!ret);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).pass_error_through(ret_void_const, "foo");
    REQUIRE(!ret);
  }
}


struct S {
    int x;
};

struct F {
    int x;
};

TEST_CASE("14", "[issue.14]") {
    auto res = tl::expected<S,F>{tl::unexpect, F{}};

    res.map_error([](F f) {

    });
}

TEST_CASE("32", "[issue.32]") {
    int i = 0;
    tl::expected<void, int> a;
    a.map([&i]{i = 42;});
    REQUIRE(i == 42);

    auto x = a.map([]{return 42;});
    REQUIRE(*x == 42);
}

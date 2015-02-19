#include <bandit/bandit.h>
using namespace bandit;

go_bandit([](){
    describe("fuzzbox:", [](){
        int a;
        int b;

        before_each([&](){
            a = 1;
            b = 2;
        });

        it("starts in clean mode", [&](){
            AssertThat(a, Equals(1));
            AssertThat(b, Equals(2));
        });

        describe("in distorted mode", [&](){
            before_each([&](){
                a += b;
            });

            it("sounds distorted", [&](){
                AssertThat(a, Equals(3));
                AssertThat(b, Equals(2));
            });
        });
    });
});

package main
import "fmt"

func main() {
    base := 2;
    power := 5;
    fmt.Println("Testing Different Strategies of exponentiation in Go:");
    fmt.Println("naive power implementation:", naive_pow(base, power));
    fmt.Println("binary exponentiation with recursion:", binary_exp(base, power));
    fmt.Println("binary exponentiation:", binary_exp_no_rec(base, power));

}

func naive_pow(base int, power int) int {
    if power == 0 {
        return 1;
    }

    if power < 0 {
        power *= -1;
        base = 1 / base;
    }

    result := 1;
    for ;power > 0; power-- {
        result *= base;
    }
    return result;
}

func binary_exp(base int, power int) int {
    if power < 0 {
        power *= -1;
        return 1 / _rec_binary_exp(base, power);
    } 
    return _rec_binary_exp(base, power);
}

func _rec_binary_exp(base int, power int) int {
    // base is accumulating (increasing), while power is decreasing
    if power == 0 {
        // base case: base^0 ∀ int = 1
        return 1;
    }

    if power % 2 == 0 {
        // when (current) power is even, square current base, half the power and continue recursion
        return _rec_binary_exp(base * base, power / 2);
    }
    // update base when current power is odd (after recursion)
    return base * _rec_binary_exp(base * base, power / 2);
}

func binary_exp_no_rec(base int, power int) int {
    is_neg_power := power < 0;
    result := 1;

    if is_neg_power {
        power *= -1;
    }

    for power > 0 {
        if power & 1 == 1 {
            result *= base;
        }
        base *= base;
        power >>= 1;
    }

    if is_neg_power {
        return 1 / result;
    }
    return result;
}



---
## Question 1: Example Code Ran

```
[kien6@atl1-1-02-004-15-2 ~]$ ./a.out
Enter number of large and small numbers to average: 20 1000000000     
running average is: 0.9773296484612657986090766826237086206675
average with large numbers first is: 0.9773296469625337712372470377886202186346
average with small numbers first: 0.9773296484592958188741818048583809286356
```

Using Welford's Algorithm as the running average, when we average the large numbers first we have 8 digits that match before it begins to differ. However, when averaging the smaller numbers first, up to 10 digits match with the running average. Therefore, summing the smaller numbers produced a more accurate result because there is less risk of a rounding error due to the limited precision that we specified (40) in the code. If we were to add the large number first then move to small numbers, the rounding would result in the discarding of some digits of the smaller double numbers to compensate for the set precision limit.

---
## Question 2: Plot of Digits of Accuracy

![[Graph View.png]]

Initially, beginning with less terms (10 to 20 terms) to evaluate, the direct approximation of e using the power series (x = 1) had the upper hand of having more accurate digits past the decimal point. However, starting with 25 terms, the direct method became stagnant at around 15 digits being accurate. The square method of approximation, on the other hand, rocketed to 40 digits matching, which was the set precision limit within the code and specifications.
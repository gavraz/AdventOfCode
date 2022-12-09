#include <stdio.h>

void init(int m[26])
{
    int i;
    for (i = 0; i < 26; i++)
    {
        m[i] = -1;
    }
}

int searchNext(char *str, const int LEN)
{
    int i, len, curr;
    int collisions[26];

    init(collisions);

    len = 0;
    for (i = 0; str[i] != '\0'; i++)
    {
        curr = str[i] - 'a';

        if (collisions[curr] != -1 && collisions[curr] > i-len-1) // collision detected
        {
            len = i - collisions[curr];
            collisions[curr] = i;
            continue;
        }

        // no collision, mark it
        
        collisions[curr] = i;
        len++;
        if (len == LEN)
        {
            return i + 1;
        }
    }

    return -1;
}

void assert(int exp, int act)
{
    if (exp != act)
    {
        printf("Assert FAILURE\tExpected:%d   Actual:%d\n", exp, act);
        return;
    }

    printf("Assert %4d  OK\n", exp);
}

void test()
{
    int res;

    res = searchNext("bvwbjplbgvbhsrlpgdmjqwftvncz", 4);
    assert(5, res);

    res = searchNext("nppdvjthqldpwncqszvftbrmjlhg", 4);
    assert(6, res);

    res = searchNext("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 4);
    assert(10, res);

    res = searchNext("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 4);
    assert(11, res);

    res = searchNext("aaaaaaabcd", 4);
    assert(10, res);

    res = searchNext("abababcd", 4);
    assert(8, res);

    res = searchNext("abcacbdcfghj", 4);
    assert(7, res);

    res = searchNext("mjqjpqmgbljsphdztnvjfqwrcgsmlb", 14);
    assert(19, res);

    res = searchNext("bvwbjplbgvbhsrlpgdmjqwftvncz", 14);
    assert(23, res);

    res = searchNext("nppdvjthqldpwncqszvftbrmjlhg", 14);
    assert(23, res);

    res = searchNext("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 14);
    assert(29, res);

    res = searchNext("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 14);
    assert(26, res);
}

int main(int argc, char **argv)
{
    int res;
    char* challenge;

    test();

    printf("---ADV-2022-06---\n");
    challenge = "czfztznzpnpqpfftcftcchfhjjsqsvvffhwfhhqnhqqmlldpdcdnnfvvmpmzpmmrsrwssqbsbsmmdjdssfqfllclcdczdccppvzvtzznpnfpnnljnnpcphpjprrdhddsgdssbqqghqqmgqgccjffdtdcdmdjdcctltdddvhdhfhnnrffwjfjpjnpnpddhbbrrflrldlqlrlqqwssqsrswrrrmcmrcrfrwfwpfpdfppslsjsjhhjjqhqwwzzhttcvvzrrrnlrlmljlrjrsshwwndnnzwzpzcpcllfrrsjsnjncjcvcllrhrbhhdsdqdpqpffmppdzztggvpvnvwvpvdvqddznzrzppznnpnhhwjjrpjpvvqvpvrvfvjvzjvzjzqzlqqwsqqrsrprqpqmmbhbffbnnlzzhszhznnhzhmzzfhflfccvvbnbtnnlcnndjjcvjjshhssfjfcjjpzpqpmmdqmqmmbbldlwwvdwvddznncwcqwcwdwbdwwgzzzqvqqlqlttbppgtptlldldblbbjcbcttbpbvvhlhggghvvqsshjhjjzqzwwcggsfgsgjjgbjgbbgllhhmqmggmsggzszvvzggdngnznlzlrlprpjpgjgvgppfhhbqqcddvvbhbqqmlmsssbbszzfdzzznssjllwlplttdgtdttsmspmpvpgpspqpdqdppfvpvvmggrwwgswswmmmnppmttqppvttrvrllcmctcqqlvvpwwghhlmhmwhmmpfmfvfwwbgbqqdbqblqqclljcljccnhhghbgbrrnrppchhmpmdmfmvffvqqtnqqfccgcfgcgwgcwggvgzvvbwbgbjbwbcbgbzztbbsbdbvddzrdrjjlqqlslrssjddhbddzbzvbvhhrjhhrtrltljljwljjrnjjjlpjphjphjhjvjgjbbwfwcctgtmtmdttjhthphhchfcfnnqlqhqvvjcclczlzwlzlhzlzdlzlbzbvbmbcmcjcncwncntndtntbbgqqbrbsrssrnnrcrmrlmmrqqddhzdhhnqqvccbmbpbwpbwbrwwwgdgnnhzzhphbhwhwzwhhvhqqnmqnmnjmnjjjjztzvzvbzbbvcvggcdchhhhbfbttmmtsmsgmmqvqdvdrvrqrdqqrhqqpsqqfnntsnnslsggcqqrnrmrfffmgmsmgggrdgdrgddzfzqfqfcqfcfrfwrrrgglwlmlmlgmlmrlljzlzglzztllgnndhdthtwwdrrjnncssdsnszsggdhdpprnnqzzltzlzznlzlflgfgbfggqtggfbbccchdcdrrnwnbnhbnbjjpzjpzzwjwcwggfqfccdzzfddmbddgbgrgllnttrwrjwrrbsrsbbwqwmmlggzqgzqzrqzzffmcmssgjjjcdcssndsdfsfddcffbrrcvccwhhzzlglhhsccvdvjjdldndrrvlrrbwrrbqqcbcjcjpjggngvnndtdvttlrlmmcbcggbtbhthjttdggtvtmmlgmlgmmdwdndmmldlttjlmbtrwfnvmnzggqfqwnppbrnjmpjfppwltpqfstgnnjwmbffgfbjmfhqngnswftgrqvpljsmghszclhhprscrgtmsgbwnbrfhwdsbjrdlhdcqfthwfggpzhjrvmprcjjgrlbmdqczmsltnpnlpldvnsjbdjzbrglpsmbwdhhphcdmjqmssdlgjtmphhjvpjqcdvmdtszldnjtbcffhwrbqpsrsmmsqsbbrnhsrvfhhcmwgcpsfhrfcpvldrwstqtgrcgrqttvdnstlbdblnbtcgdgpbcjdlvwpplsslqdsbpncbwzcmlglbhnrtbwvnbfsgrdlpzszhzmzqtztzgjjjszmjgggdnslqqqrrlwcghpvzwpndbjbhhhpbbtvjvjvjhntqggtmqwdnrtswcchsqpdwnvmfqrgpvbtjpttfhmlgtnsgnpcrhbswfblwrbflqlgtmvzvwprtfntshjcpzshnlnqthvqgpzffsbdbvbhpghwjhqpjwjfbsrzgttsnrpmfrvlwrjrfplrtzpntjbvhdjjfjjzrrvrsrctrtldrsgcgvntgvmtrnqbtmpzvlbwnddbnldbhfcpncqclzqgmbjcnnfdfsmdjdgtmtzbpwqrhrlggrfjhvrrqpjptqdzpwffwnfwmfhfhmcpljmhttbltgltqjhtvbdzgwrppzjwhctnncqthnlrhzgtnffpwnnqqgddjtgtczfmwvbccgvmdfvggdghmssjlflptzrpdncbjcsdlbqjfzmnzdggwdczghfpldsbnvzdjzsbsdnmwptgngmnbqmwbrzqgnqbmfvbzzmsvlswbtvfllqzsjdlvzjmbmlbnljwwjsqzqvfwhzmfdgttfqsdttnjmvspsgvpzwczpvdbvhjjrttghjddrgffqdsmzspnssztjjmwtsrtlrmbqhfbvpzsmnqthssbqrjhvqllrbbpjjllszmnjvzmfsbjtvvvgzrvjwldlbzjdbrsvvgmmjrgsbvtvthjbcqlzqhjqfvbzzvlpmrlmphftwbsvvwnwqfwvsnlvlcdgqjspprmwptcjhbjplzrqlhmvzmbfvwwvgvtqlvgfvzqdprfcjqsnndwqmbhlvfvhdhghtsrhbcrrshlsdtlbwntbcvvjhlcscfcnhbdnngtsccrnfbbqbfggvwnmlfhmqbdqpnzvzcvngcctbrshsdvhstcnwvjgwchzdndgbgjnddrmfgftvvjtdnqhfjmpjcjjtmgztvnwnrjjgmcgcqclnwvclngrtjggrprmfpqcsmdtbswhwrgwgfflqldtpnfdhdltrnhdvqqdsshcrnncdpvbhvlcbjlznjjzsdcjjpqprnzpmvqvrfnhdvhgrsmlcgtbsmrgqqtmblqmqcnmnmbcmmjvnptzbbqmcpwbflhccpfrjvfzmcsttfjtjgrnjbtwbncrsjjgjwdpmvfpqmzqwgjvgvfnpbhgzlzhfsnwmjjjsgcjjcwcfbzrmfzwdmhffqnzscbnfmpnbdbccrsjgqgvftszdbqbstwtwmwfzbtmvdmwvshlcpqnsqfwqlfclmjdjvgszsdblwvnhtwtrjcwsmpgflhdqmndrjvqlhqclmwhscnznmhjtqjlnglpbmgvptjnrpnjlqslssfnbdwlrwrdrtfspsjwzvwzfjpflqgmfnbvzqglrrccsnqtchnhlnrwlwqmqdvwsjmbjbvczvqcgfrrtftcgqsnvzhjlshnlvqmvrjljpsvmdzwqgltmccnplbmplhpvvflhmgfzmhczpwffbzhzhhggzgwtpmlzgrbpfgcnmfdbgcwrbgdpzpwmtwgmjtpmqzzgclmcpjgzdrwqfdwqzzqszrwmbwcqzcjdphqtwlbqmnddsdthgjrlshhmzgrqlhghrbqgzppqbdmmlnthhhmtdcdnbqfvbwdrdgbbpbhtrflwmhwjmzdtwmzhjndbrvbtbqnzbsrrbfdrrdnjltdtsjnpddmqzzbzblzvwctpdhfqgqntczwlgqbvvmhjblztlpptqjscztlrvrglrbsbfdjdfbwjltjcdgmqzgtjqjfgjnnpqgfhsrcggrszhbgfhtjmlgmmvshcpjwmcwcvwhnbjzrzfwtnlsnmdgfpbhvgfrhmhmsmtrnblsmnjclqzfgttrdmvpsvlcvnhmgmltfhffzllfrmdqdpzdmjdmsnmpwbwvrdvwvrcdsfwftfbfvmzjttrqgqlqqdtmcpdpfqfsclcmcdzhjwqrbhmzjjsvpbjzzgfwbjbqmzmtrnflwrqgnbgqnpntqmlngmgcrflgvhpznvrfwzlwrswbdsldfdbhvwvcbwhmpcslhmmbjdzvmgrjwzqqzlrrgddpssqcshzrsvrrzzcbsgvfmrlcgjrcpphctdwtjbmrlnrmrbgsqbjnmnsbjfhszcgdqfflcwvrvnwtvcnhcffvphwmzqpwnwncrbnzrnvjzsrnlzlfdbgztrhvlvpczzqnwsvwvnhgnclhndjsgqdgznjzrtmslmgnjzpj";

    res = searchNext(challenge, 4);
    printf("1. Answer: %d\n", res);
    res = searchNext(challenge, 14);
    printf("2. Answer: %d\n", res);

    return 0;
}
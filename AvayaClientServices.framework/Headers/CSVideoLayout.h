/* Copyright Avaya Inc. */

/**
 * Enumeration of all of the video layouts supported during a conference call.
 * Local user can select from any of these layouts to effect the video image rendered on the client.
 * With the exception of CSVideoLayoutDynamic, the rest of the layout options allow user
 * to specify a fixed layout of the video rendered on the local client.
 * When the layout is set to be dynamic, the conference server updates the layout of the rendered
 * video automatically.
 * The list of actual video layouts available may change dynamically while on a call,
 * dependent on the capabilities of the conferencing system, number of video participants 
 * on a call, and whether local user is a lecturer or not.
 * The integers provided with each layout below represent indices of different video 
 * windows (a.k.a., sub-frame), as recognized by the conferencing system. These video window
 * ids can be used to pin a participant's video.
 */

typedef NS_ENUM(NSUInteger, CSVideoLayout) {

	/**
	 * Indicates that video layout selection is not supported.
	 */
	CSVideoLayoutNone = 0,
	
	/**
	 * Server automatically determines best layout, and updates the video image accordingly.
	 */
	CSVideoLayoutDynamic,
	
	/**
	 * Single full-screen video.
	 * <p><pre>
	 *  __________________
	 *  |                |
	 *  |                |
	 *  |                |
	 *  |       0        |
	 *  |                |
	 *  |                |
	 *  |________________|
	 * </pre></p>
	 */
	CSVideoLayoutOneVideoWindowOptionOne,

	/**
	 * Full-screen presentation video.
	 * <p><pre>
	 *  __________________
	 *  |                |
	 *  |                |
	 *  |       0        |
	 *  |  Presentation  |
	 *  |                |
	 *  |                |
	 *  |________________|
	 * </pre></p>
	 */
	CSVideoLayoutOneVideoWindowOptionTwoWithPresentation,

	/**
	 * Two smaller landscape videos tiled next to one another.
	 * <p><pre>
	 *  _________________
	 *  |       |       |
	 *  |   0   |  1    |
	 *  |_______|_______|
	 * </pre></p>
	 */
	CSVideoLayoutTwoVideoWindowsOptionOne,

	/**
	 * Two smaller landscape videos tiled above one another.
	 * <p><pre>
	 *  _________
	 *  |       |
	 *  |   0   |
	 *  |_______|
	 *  |       |
	 *  |   1   |
	 *  |_______|
	 * </pre></p>
	 */
	CSVideoLayoutTwoVideoWindowsOptionTwo,

	/**
	 * Two videos next to each other, large one to the left, 
	 * smaller one to the right.
	 * <p><pre>
	 *  ____________
	 *  |          |
	 *  |          |
	 *  |    0     |______
	 *  |          |  1  |
	 *  |__________|_____|
	 * </pre></p>
	 */
	CSVideoLayoutTwoVideoWindowsOptionThree,

	/**
	 * Two videos, one full screen, the other a small video overlaid 
	 * in the lower center of the screen.
	 * <p><pre>
	 *  _________________
	 *  |               |
	 *  |               |
	 *  |       0       |
	 *  |    _______    |
	 *  |    |  1  |    |
	 *  |____|_____|____|
	 * </pre></p>
	 */
	CSVideoLayoutTwoVideoWindowsOptionFour,

	/**
	 * Three landscape videos, one above center, 
	 * two tiled horizontally underneath.
	 * <p><pre>
	 *     __________
	 *     |        |
	 *     |   0    |
	 *  ___|________|____
	 *  |   1   |   2   |
	 *  |_______|_______|
	 * </pre></p>
	 */
	CSVideoLayoutThreeVideoWindowsOptionOne,

	/**
	 * Three videos, one large landscape next to two smaller 
	 * videos tiled one on top of the other to the right.
	 * <p><pre>
	 *  _________________
	 *  |         |  1  |
	 *  |    0    |_____|
	 *  |         |  2  |
	 *  |_________|_____|
	 * </pre></p>
	 */
	CSVideoLayoutThreeVideoWindowsOptionTwo,

	/**
	 * Three videos, one full screen, two overlaid in the lower center
	 * of the screen.
	 * <p><pre>
	 *  _________________
	 *  |               |
	 *  |               |
	 *  |       0       |
	 *  |   _________   |
	 *  |   | 1 | 2 |   |
	 *  |___|___|___|___|
	 * </pre></p>
	 */
	CSVideoLayoutThreeVideoWindowsOptionThree,

	/**
	 * Three videos horizontally positioned in the middle
	 * of the available space.
	 * <p><pre>
	 *  _________________
	 *  |               |
	 *  |_______________|
	 *  | 0  | 1  |  2  |
	 *  |____|____|_____|
	 *  |               |
	 *  |_______________|
	 * </pre></p>
	 */
	CSVideoLayoutThreeVideoWindowsOptionFour,

	/**
	 * Four landscape videos of equal size, two in the top row, 
	 * two in the bottom row, full square.
	 * <p><pre>
	 *  _________________
	 *  |   0   |   1   |
	 *  |_______|_______|
	 *  |   2   |   3   |
	 *  |_______|_______|
	 * </pre></p>
	 */
	CSVideoLayoutFourVideoWindowsOptionOne,

	/**
	 * Four videos in two rows, one large video on top, 
	 * three smaller ones underneath.
	 * <p><pre>
	 *     __________
	 *     |   0    |
	 *     |        |
	 *  ___|________|____
	 *  |  1 | 2  |  3  |
	 *  |____|____|_____|
	 * </pre></p>
	 */
	CSVideoLayoutFourVideoWindowsOptionTwo,

	/**
	 * Four videos, one large landscape next to three smaller videos 
	 * tiled one on top of the other to the right.
	 * <p><pre>
	 *  _________________
	 *  |         |  1  |
	 *  |         |_____|
	 *  |    0    |  2  |
	 *  |         |_____|
	 *  |         |  3  |
	 *  |_________|_____|
	 * </pre></p>
	 */
	CSVideoLayoutFourVideoWindowsOptionThree,

	/**
	 * Four videos, one full screen, three overlaid in the lower 
	 * center of the screen.
	 * <p><pre>
	 *  _____________________
	 *  |                   |
	 *  |         0         |
	 *  |                   |
	 *  |   _____________   |
	 *  |   | 1 | 2 | 3 |   |
	 *  |___|___|___|___|___|
	 * </pre></p>
	 */
	CSVideoLayoutFourVideoWindowsOptionFour,

	/**
	 * Five videos in two rows, one large video on top, 
	 * four smaller ones underneath.
	 * <p><pre>
	 *    _____________
	 *    |           |
	 *    |     0     |
	 *    |           |
	 *  __|___________|__
	 *  | 1 | 2 | 3 | 4 |
	 *  |___|___|___|___|
	 * </pre></p>
	 */
	CSVideoLayoutFiveVideoWindowsOptionOne,

	/**
	 * Five videos, one full screen, four overlaid in the 
	 * lower center of the screen.
	 * <p><pre>
	 *  _________________________
	 *  |                       |
	 *  |           0           |
	 *  |                       |
	 *  |   _________________   |
	 *  |   | 1 | 2 | 3 | 4 |   |
	 *  |___|___|___|___|___|___|
	 * </pre></p>
	 */
	CSVideoLayoutFiveVideoWindowsOptionTwo,

	/**
	 * One large presentation video with four smaller person video below.
	 * <p><pre>
	 *  _________________
	 *  |               |
	 *  |      0        |
	 *  |  Presentation |
	 *  |_______________|
	 *  | 1 | 2 | 3 | 4 |
	 *  |___|___|___|___|
	 * </pre></p>
	 */
	CSVideoLayoutFiveVideoWindowsOptionThreeWithPresentation,

	/**
	 * One large presentation video, four smaller person video tiled 
	 * vertically to the right of the presentation video.
	 * <p><pre>
	 *  ______________________
	 *  |                | 1 |
	 *  |                |___|
	 *  |        0       | 2 |
	 *  |  Presentation  |___|
	 *  |                | 3 |
	 *  |                |___|
	 *  |                | 4 |
	 *  |________________|___|
	 * </pre></p>
	 */
	CSVideoLayoutFiveVideoWindowsOptionFourWithPresentation,

	/**
	 * Six videos, one large landscape next to two smaller videos 
	 * to the right tiled one on top of the other, and three smaller 
	 * videos next to each other underneath.
	 * <p><pre>
	 *  _________________
	 *  |         |  1  |
	 *  |    0    |_____|
	 *  |         |  2  |
	 *  |_________|_____|
	 *  | 3  | 4  |  5  |
	 *  |____|____|_____|
	 * </pre></p>
	 */
	CSVideoLayoutSixVideoWindowsOptionOne,

	/**
	 * Six landscape videos of equal size arranged in two rows.
	 * <p><pre>
	 *  _________________
	 *  |    |    |     |
	 *  |  0 |  1 |  2  |
	 *  |____|____|_____|
	 *  |    |    |     |
	 *  |  3 |  4 |  5  |
	 *  |____|____|_____|
	 * </pre></p>
	 */
	CSVideoLayoutSixVideoWindowsOptionTwo,

	/**
	 * Seven videos, one large landscape next to 
	 * two smaller videos to the right tiled one on top of the other,
	 * and four smaller videos next to each other underneath.
	 * <p><pre>
	 *  _________________
	 *  |         |  1  |
	 *  |    0    |_____|
	 *  |         |  2  |
	 *  |_________|_____|
	 *  | 3 | 4 | 5 | 6 |
	 *  |___|___|___|___|
	 * </pre></p>
	 */
	CSVideoLayoutSevenVideoWindowsOptionOne,

	/**
	 * One large presentation video with six smaller person video below.
	 * <p><pre>
	 *  _________________________
	 *  |                       |
	 *  |                       |
	 *  |           0           |
	 *  |      Presentation     |
	 *  |                       |
	 *  |_______________________|
	 *  | 1 | 2 | 3 | 4 | 5 | 6 |
	 *  |___|___|___|___|___|___|
	 * </pre></p>
	 */
	CSVideoLayoutSevenVideoWindowsOptionTwoWithPresentation,

	/**
	 * One large presentation video, six smaller person video tiled
	 * vertically to the right of the presentation video.
	 * <p><pre>
	 *  _________________________
	 *  |                   | 1 |
	 *  |                   |___|
	 *  |                   | 2 |
	 *  |                   |___|
	 *  |                   | 3 |
	 *  |          0        |___|
	 *  |    Presentation   | 4 |
	 *  |                   |___|
	 *  |                   | 5 |
	 *  |                   |___|
	 *  |                   | 6 |
	 *  |___________________|___|
	 * </pre></p>
	 */
	CSVideoLayoutSevenVideoWindowsOptionThreeWithPresentation,

	/**
	 * Eight videos, one large landscape next to three smaller
	 * videos to the right tiled one on top of the other, and
	 * four smaller videos next to each other underneath.
	 * <p><pre>
	 *  _________________
	 *  |           | 1 |
	 *  |           |___|
	 *  |     0     | 2 |
	 *  |           |___|
	 *  |           | 3 |
	 *  |___________|___|
	 *  | 4 | 5 | 6 | 7 |
	 *  |___|___|___|___|
	 * </pre></p>
	 */
	CSVideoLayoutEightVideoWindowsOptionOne,

	/**
	 * Eight videos of equal size arranged in two rows of four.
	 * <p><pre>
	 *  _____________________
	 *  |    |    |    |    |
	 *  | 0  | 1  | 2  | 3  |
	 *  |____|____|____|____|
	 *  |    |    |    |    |
	 *  | 4  | 5  | 6  | 7  |
	 *  |____|____|____|____|
	 * </pre></p>
	 */
	CSVideoLayoutEightVideoWindowsOptionTwo,

	/**
	 * Nine videos of equal size arranged in three rows, three per row.
	 * <p><pre>
	 *  _____________
	 *  | 0 | 1 | 2 |
	 *  |___|___|___|
	 *  | 3 | 4 | 5 |
	 *  |___|___|___|
	 *  | 6 | 7 | 8 |
	 *  |___|___|___|
	 * </pre></p>
	 */
	CSVideoLayoutNineVideoWindowsOptionOne,

	/**
	 * Nine videos, one larger on top and eight smaller ones 
	 * beneath arranged in two rows of four.
	 * <p><pre>
	 *     _________
	 *     |       |
	 *     |   0   |
	 *  ___|_______|_____
	 *  | 1 | 2 | 3 | 4 |
	 *  |___|___|___|___|
	 *  | 5 | 6 | 7 | 8 |
	 *  |___|___|___|___|
	 * </pre></p>
	 */
	CSVideoLayoutNineVideoWindowsOptionTwo,

	/**
	 * Ten videos where the top two quadrants contain two larger videos,
	 * while the lower two quadrants have four videos in each.
	 * <p><pre>
	 *  _________________
	 *  |       |       |
	 *  |   0   |   1   |
	 *  |_______|_______|
	 *  | 2 | 3 | 4 | 5 |
	 *  |___|___|___|___|
	 *  | 6 | 7 | 8 | 9 |
	 *  |___|___|___|___|
	 * </pre></p>
	 */
	CSVideoLayoutTenVideoWindowsOptionOne,

	/**
	 * Twelve videos of equal size arranged in three rows, four per row.
	 * <p><pre>
	 *  _________________
	 *  | 0 | 1 | 2 | 3 |
	 *  |___|___|___|___|
	 *  | 4 | 5 | 6 | 7 |
	 *  |___|___|___|___|
	 *  | 8 | 9 | 10| 11|
	 *  |___|___|___|___|
	 * </pre></p>
	 */
	CSVideoLayoutTwelveVideoWindowsOptionOne,

	/**
	 * Thirteen videos where the top left quadrant has a large video, 
	 * the remaining three quadrants have four videos each.
	 * <p><pre>
	 *  _________________
	 *  |       | 1 | 2 |
	 *  |   0   |___|___|
	 *  |       | 3 | 4 |
	 *  |_______|___|___|
	 *  | 5 | 6 | 7 | 8 |
	 *  |___|___|___|___|
	 *  | 9 | 10| 11| 12|
	 *  |___|___|___|___|
	 * </pre></p>
	 */
	CSVideoLayoutThirteenVideoWindowsOptionOne,

	/**
	 * Thirteen videos, one large video in the center surrounded 
	 * by Twelve smaller equally sized videos around the edge of the screen.
	 * <p><pre>
	 *  _________________
	 *  | 1 | 2 | 3 | 4 |
	 *  |___|___|___|___|
	 *  | 5 |       | 6 |
	 *  |___|   0   |___|
	 *  | 7 |       | 8 |
	 *  |___|_______|___|
	 *  | 9 | 10| 11| 12|
	 *  |___|___|___|___|
	 * </pre></p>
	 */
	CSVideoLayoutThirteenVideoWindowsOptionTwo,

	/**
	 * Sixteen videos of the same size, arranged in four rows of four.
	 * <p><pre>
	 *  _________________
	 *  | 0 | 1 | 2 | 3 |
	 *  |___|___|___|___|
	 *  | 4 | 5 | 6 | 7 |
	 *  |___|___|___|___|
	 *  | 8 | 9 |10 |11 |
	 *  |___|___|___|___|
	 *  |12 |13 |14 |15 |
	 *  |___|___|___|___|
	 * </pre></p>
	 */
	CSVideoLayoutSixteenVideoWindowsOptionOne,

	/**
	 * Twenty one videos, one large video in the center surrounded by 
	 * twenty smaller equally sized videos around the edge of the screen.
	 * <p><pre>
	 *  ___________________
	 *  |1 |2 |3 |4 |5 |6 |
	 *  |__|__|__|__|__|__|
	 *  |7 |           |8 |
	 *  |__|           |__|
	 *  |9 |           |10|
	 *  |__|     0     |__|
	 *  |11|           |12|
	 *  |__|           |__|
	 *  |13|           |14|
	 *  |__|___________|__|
	 *  |15|16|17|18|19|20|
	 *  |__|__|__|__|__|__|
	 * </pre></p>
	 */
	CSVideoLayoutTwentyOneVideoWindowsOptionOne,

	/**
	 * Twenty one videos, one large video in the top left corner, 
	 * eight videos to the right, tiled two across, 
	 * and Twelve videos underneath in two rows of six.
	 * <p><pre>
	 *  ___________________
	 *  |         | 1 | 2 |
	 *  |         |___|___|
	 *  |         | 3 | 4 |
	 *  |    0    |___|___|
	 *  |         | 5 | 6 |
	 *  |         |___|___|
	 *  |         | 7 | 8 |
	 *  |_________|___|___|
	 *  | 9|10|11|12|13|14|
	 *  |__|__|__|__|__|__|
	 *  |15|16|17|18|19|20|
	 *  |__|__|__|__|__|__|
	 * </pre></p>
	 */
	CSVideoLayoutTwentyOneVideoWindowsOptionTwo,

	/**
	 * Twenty eight videos, one large video in the top left quadrant, 
	 * and nine videos in each of the remaining three quadrants.
	 * <p><pre>
	 *  ___________________
	 *  |        |1 |2 |3 |
	 *  |        |__|__|__|
	 *  |   0    |4 |5 |6 |
	 *  |        |__|__|__|
	 *  |        |7 |8 |9 |
	 *  |________|__|__|__|
	 *  |10|11|12|13|14|15|
	 *  |__|__|__|__|__|__|
	 *  |16|17|18|19|20|21|
	 *  |__|__|__|__|__|__|
	 *  |22|23|24|25|26|27|
	 *  |__|__|__|__|__|__|
	 * </pre></p>
	 */
	CSVideoLayoutTwentyEightVideoWindowsOptionOne
};

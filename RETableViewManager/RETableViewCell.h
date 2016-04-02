//
// RETableViewCell.h
// RETableViewManager
//
// Copyright (c) 2013 Roman Efimov (https://github.com/romaonthego)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#import <UIKit/UIKit.h>
#import "RETableViewSection.h"
#import "REActionBar.h"

@class RETableViewManager;
@class RETableViewItem;

@class RETableViewCell;

/**
 * This is a convenience class to create RETableViewCell buttons
 * Using this class is optional because RETableViewCell is button agnostic and can use any UIView for that purpose
 * Anyway, it's recommended that you use this class because is totally tested and easy to use ;)
 */
@interface MGSwipeButton : UIButton

/**
 * Convenience block callback for developers lazy to implement the RETableViewCellDelegate.
 * @return Return YES to autohide the swipe view
 */
typedef BOOL(^MGSwipeButtonCallback)(RETableViewCell * sender);
@property (nonatomic, strong) MGSwipeButtonCallback callback;

/** A width for the expanded buttons. Defaults to 0, which means sizeToFit will be called. */
@property (nonatomic, assign) CGFloat buttonWidth;

/**
 * Convenience static constructors
 */
+(instancetype) buttonWithTitle:(NSString *) title backgroundColor:(UIColor *) color;
+(instancetype) buttonWithTitle:(NSString *) title backgroundColor:(UIColor *) color padding:(NSInteger) padding;
+(instancetype) buttonWithTitle:(NSString *) title backgroundColor:(UIColor *) color insets:(UIEdgeInsets) insets;
+(instancetype) buttonWithTitle:(NSString *) title backgroundColor:(UIColor *) color callback:(MGSwipeButtonCallback) callback;
+(instancetype) buttonWithTitle:(NSString *) title backgroundColor:(UIColor *) color padding:(NSInteger) padding callback:(MGSwipeButtonCallback) callback;
+(instancetype) buttonWithTitle:(NSString *) title backgroundColor:(UIColor *) color insets:(UIEdgeInsets) insets callback:(MGSwipeButtonCallback) callback;
+(instancetype) buttonWithTitle:(NSString *) title icon:(UIImage*) icon backgroundColor:(UIColor *) color;
+(instancetype) buttonWithTitle:(NSString *) title icon:(UIImage*) icon backgroundColor:(UIColor *) color padding:(NSInteger) padding;
+(instancetype) buttonWithTitle:(NSString *) title icon:(UIImage*) icon backgroundColor:(UIColor *) color insets:(UIEdgeInsets) insets;
+(instancetype) buttonWithTitle:(NSString *) title icon:(UIImage*) icon backgroundColor:(UIColor *) color callback:(MGSwipeButtonCallback) callback;
+(instancetype) buttonWithTitle:(NSString *) title icon:(UIImage*) icon backgroundColor:(UIColor *) color padding:(NSInteger) padding callback:(MGSwipeButtonCallback) callback;
+(instancetype) buttonWithTitle:(NSString *) title icon:(UIImage*) icon backgroundColor:(UIColor *) color insets:(UIEdgeInsets) insets callback:(MGSwipeButtonCallback) callback;

-(void) setPadding:(CGFloat) padding;
-(void) setEdgeInsets:(UIEdgeInsets)insets;
-(void) centerIconOverText;
-(void) centerIconOverTextWithSpacing: (CGFloat) spacing;

@end

/** Transition types */
typedef NS_ENUM(NSInteger, MGSwipeTransition) {
    MGSwipeTransitionBorder = 0,
    MGSwipeTransitionStatic,
    MGSwipeTransitionDrag,
    MGSwipeTransitionClipCenter,
    MGSwipeTransitionRotate3D
};

/** Compatibility with older versions */
#define MGSwipeTransition3D MGSwipeTransitionRotate3D
#define MGSwipeStateSwippingLeftToRight MGSwipeStateSwipingLeftToRight
#define MGSwipeStateSwippingRightToLeft MGSwipeStateSwipingRightToLeft

/** Swipe directions */
typedef NS_ENUM(NSInteger, MGSwipeDirection) {
    MGSwipeDirectionLeftToRight = 0,
    MGSwipeDirectionRightToLeft
};

/** Swipe state */
typedef NS_ENUM(NSInteger, MGSwipeState) {
    MGSwipeStateNone = 0,
    MGSwipeStateSwipingLeftToRight,
    MGSwipeStateSwipingRightToLeft,
    MGSwipeStateExpandingLeftToRight,
    MGSwipeStateExpandingRightToLeft,
};

/** Swipe state */
typedef NS_ENUM(NSInteger, MGSwipeExpansionLayout) {
    MGSwipeExpansionLayoutBorder = 0,
    MGSwipeExpansionLayoutCenter
};

/** Swipe Easing Function */
typedef NS_ENUM(NSInteger, MGSwipeEasingFunction) {
    MGSwipeEasingFunctionLinear = 0,
    MGSwipeEasingFunctionQuadIn,
    MGSwipeEasingFunctionQuadOut,
    MGSwipeEasingFunctionQuadInOut,
    MGSwipeEasingFunctionCubicIn,
    MGSwipeEasingFunctionCubicOut,
    MGSwipeEasingFunctionCubicInOut,
    MGSwipeEasingFunctionBounceIn,
    MGSwipeEasingFunctionBounceOut,
    MGSwipeEasingFunctionBounceInOut
};

/**
 * Swipe animation settings
 **/
@interface MGSwipeAnimation : NSObject
/** Animation duration in seconds. Default value 0.3 */
@property (nonatomic, assign) CGFloat duration;
/** Animation easing function. Default value EaseOutBounce */
@property (nonatomic, assign) MGSwipeEasingFunction easingFunction;
/** Override this method to implement custom easing functions */
-(CGFloat) value:(CGFloat) elapsed duration:(CGFloat) duration from:(CGFloat) from to:(CGFloat) to;

@end

/**
 * Swipe settings
 **/
@interface MGSwipeSettings: NSObject
/** Transition used while swiping buttons */
@property (nonatomic, assign) MGSwipeTransition transition;
/** Size proportional threshold to hide/keep the buttons when the user ends swiping. Default value 0.5 */
@property (nonatomic, assign) CGFloat threshold;
/** Optional offset to change the swipe buttons position. Relative to the cell border position. Default value: 0
 ** For example it can be used to avoid cropped buttons when sectionIndexTitlesForTableView is used in the UITableView
 **/
@property (nonatomic, assign) CGFloat offset;
/** Top margin of the buttons relative to the contentView */
@property (nonatomic, assign) CGFloat topMargin;
/** Bottom margin of the buttons relative to the contentView */
@property (nonatomic, assign) CGFloat bottomMargin;

/** Animation settings when the swipe buttons are shown */
@property (nonatomic, strong) MGSwipeAnimation * showAnimation;
/** Animation settings when the swipe buttons are hided */
@property (nonatomic, strong) MGSwipeAnimation * hideAnimation;
/** Animation settings when the cell is stretched from the swipe buttons */
@property (nonatomic, strong) MGSwipeAnimation * stretchAnimation;

/** Property to read or change swipe animation durations. Default value 0.3 */
@property (nonatomic, assign) CGFloat animationDuration DEPRECATED_ATTRIBUTE;

/** If true the buttons are kept swiped when the threshold is reached and the user ends the gesture
 * If false, the buttons are always hidden when the user ends the swipe gesture
 */
@property (nonatomic, assign) BOOL keepButtonsSwiped;

/** If true the table cell is not swiped, just the buttons **/
@property (nonatomic, assign) BOOL onlySwipeButtons;

/** If NO the swipe bounces will be disabled, the swipe motion will stop right after the button */
@property (nonatomic, assign) BOOL enableSwipeBounces;

@end


/**
 * Expansion settings to make expandable buttons
 * Swipe button are not expandable by default
 **/
@interface MGSwipeExpansionSettings: NSObject
/** index of the expandable button (in the left or right buttons arrays) */
@property (nonatomic, assign) NSInteger buttonIndex;
/** if true the button fills the cell on trigger, else it bounces back to its initial position */
@property (nonatomic, assign) BOOL fillOnTrigger;
/** Size proportional threshold to trigger the expansion button. Default value 1.5 */
@property (nonatomic, assign) CGFloat threshold;
/** Optional expansion color. Expanded button's background color is used by default **/
@property (nonatomic, strong) UIColor * expansionColor;
/** Defines the layout of the expanded button **/
@property (nonatomic, assign) MGSwipeExpansionLayout expansionLayout;
/** Animation settings when the expansion is triggered **/
@property (nonatomic, strong) MGSwipeAnimation * triggerAnimation;

/** Property to read or change expansion animation durations. Default value 0.2
 * The target animation is the change of a button from normal state to expanded state
 */
@property (nonatomic, assign) CGFloat animationDuration;
@end


/** helper forward declaration */
@class RETableViewCell;

/**
 * Optional delegate to configure swipe buttons or to receive triggered actions.
 * Buttons can be configured inline when the cell is created instead of using this delegate,
 * but using the delegate improves memory usage because buttons are only created in demand
 */
@protocol RETableViewCellDelegate <NSObject>

@optional
/**
 * Delegate method to enable/disable swipe gestures
 * @return YES if swipe is allowed
 **/
-(BOOL) swipeTableCell:(RETableViewCell*) cell canSwipe:(MGSwipeDirection) direction fromPoint:(CGPoint) point;
-(BOOL) swipeTableCell:(RETableViewCell*) cell canSwipe:(MGSwipeDirection) direction DEPRECATED_ATTRIBUTE; //backwards compatibility

/**
 * Delegate method invoked when the current swipe state changes
 @param state the current Swipe State
 @param gestureIsActive YES if the user swipe gesture is active. No if the uses has already ended the gesture
 **/
-(void) swipeTableCell:(RETableViewCell*) cell didChangeSwipeState:(MGSwipeState) state gestureIsActive:(BOOL) gestureIsActive;

/**
 * Called when the user clicks a swipe button or when a expandable button is automatically triggered
 * @return YES to autohide the current swipe buttons
 **/
-(BOOL) swipeTableCell:(RETableViewCell*) cell tappedButtonAtIndex:(NSInteger) index direction:(MGSwipeDirection)direction fromExpansion:(BOOL) fromExpansion;
/**
 * Delegate method to setup the swipe buttons and swipe/expansion settings
 * Buttons can be any kind of UIView but it's recommended to use the convenience MGSwipeButton class
 * Setting up buttons with this delegate instead of using cell properties improves memory usage because buttons are only created in demand
 * @param swipeTableCell the UITableVieCel to configure. You can get the indexPath using [tableView indexPathForCell:cell]
 * @param direction The swipe direction (left to right or right to left)
 * @param swipeSettings instance to configure the swipe transition and setting (optional)
 * @param expansionSettings instance to configure button expansions (optional)
 * @return Buttons array
 **/
-(NSArray*) swipeTableCell:(RETableViewCell*) cell swipeButtonsForDirection:(MGSwipeDirection)direction
             swipeSettings:(MGSwipeSettings*) swipeSettings expansionSettings:(MGSwipeExpansionSettings*) expansionSettings;

/**
 * Called when the user taps on a swiped cell
 * @return YES to autohide the current swipe buttons
 **/
-(BOOL) swipeTableCell:(RETableViewCell *)cell shouldHideSwipeOnTap:(CGPoint) point;

/**
 * Called when the cell will begin swiping
 * Useful to make cell changes that only are shown after the cell is swiped open
 **/
-(void) swipeTableCellWillBeginSwiping:(RETableViewCell *) cell;

/**
 * Called when the cell will end swiping
 **/
-(void) swipeTableCellWillEndSwiping:(RETableViewCell *) cell;

@end



typedef NS_ENUM(NSInteger, RETableViewCellType) {
    RETableViewCellTypeFirst,
    RETableViewCellTypeMiddle,
    RETableViewCellTypeLast,
    RETableViewCellTypeSingle,
    RETableViewCellTypeAny
};

/**
 The `RETableViewCell` class defines the attributes and behavior of the cells that appear in `UITableView` objects.
 
 */
@interface RETableViewCell : UITableViewCell <REActionBarDelegate>

/** optional delegate (not retained) */
@property (nonatomic, weak) id<RETableViewCellDelegate> delegate;

/** optional to use contentView alternative. Use this property instead of contentView to support animated views while swiping */
@property (nonatomic, strong, readonly) UIView * swipeContentView;

/**
 * Left and right swipe buttons and its settings.
 * Buttons can be any kind of UIView but it's recommended to use the convenience MGSwipeButton class
 */
@property (nonatomic, copy) NSArray * leftButtons;
@property (nonatomic, copy) NSArray * rightButtons;
@property (nonatomic, strong) MGSwipeSettings * leftSwipeSettings;
@property (nonatomic, strong) MGSwipeSettings * rightSwipeSettings;

/** Optional settings to allow expandable buttons */
@property (nonatomic, strong) MGSwipeExpansionSettings * leftExpansion;
@property (nonatomic, strong) MGSwipeExpansionSettings * rightExpansion;

/** Readonly property to fetch the current swipe state */
@property (nonatomic, readonly) MGSwipeState swipeState;
/** Readonly property to check if the user swipe gesture is currently active */
@property (nonatomic, readonly) BOOL isSwipeGestureActive;

// default is NO. Controls whether multiple cells can be swiped simultaneously
@property (nonatomic) BOOL allowsMultipleSwipe;
// default is NO. Controls whether buttons with different width are allowed. Buttons are resized to have the same size by default.
@property (nonatomic) BOOL allowsButtonsWithDifferentWidth;
//default is YES. Controls whether swipe gesture is allowed when the touch starts into the swiped buttons
@property (nonatomic) BOOL allowsSwipeWhenTappingButtons;
//default is YES. Controls whether swipe gesture is allowed in opposite directions. NO value disables swiping in opposite direction once started in one direction
@property (nonatomic) BOOL allowsOppositeSwipe;
// default is NO.  Controls whether the cell selection/highlight status is preserved when expansion occurs
@property (nonatomic) BOOL preservesSelectionStatus;
/* default is NO. Controls whether dismissing a swiped cell when tapping outside of the cell generates a real touch event on the other cell.
 Default behaviour is the same as the Mail app on iOS. Enable it if you want to allow to start a new swipe while a cell is already in swiped in a single step.  */
@property (nonatomic) BOOL touchOnDismissSwipe;

/** Optional background color for swipe overlay. If not set, its inferred automatically from the cell contentView */
@property (nonatomic, strong) UIColor * swipeBackgroundColor;
/** Property to read or change the current swipe offset programmatically */
@property (nonatomic, assign) CGFloat swipeOffset;

/** Utility methods to show or hide swipe buttons programmatically */
-(void) hideSwipeAnimated: (BOOL) animated;
-(void) hideSwipeAnimated: (BOOL) animated completion:(void(^)(BOOL finished)) completion;
-(void) showSwipe: (MGSwipeDirection) direction animated: (BOOL) animated;
-(void) showSwipe: (MGSwipeDirection) direction animated: (BOOL) animated completion:(void(^)(BOOL finished)) completion;
-(void) setSwipeOffset:(CGFloat)offset animated: (BOOL) animated completion:(void(^)(BOOL finished)) completion;
-(void) setSwipeOffset:(CGFloat)offset animation: (MGSwipeAnimation *) animation completion:(void(^)(BOOL finished)) completion;
-(void) expandSwipe: (MGSwipeDirection) direction animated: (BOOL) animated;

/** Refresh method to be used when you want to update the cell contents while the user is swiping */
-(void) refreshContentView;
/** Refresh method to be used when you want to dynamically change the left or right buttons (add or remove)
 * If you only want to change the title or the backgroundColor of a button you can change it's properties (get the button instance from leftButtons or rightButtons arrays)
 * @param usingDelegate if YES new buttons will be fetched using the RETableViewCellDelegate. Otherwise new buttons will be fetched from leftButtons/rightButtons properties.
 */
-(void) refreshButtons: (BOOL) usingDelegate;

///-----------------------------
/// @name Accessing Table View and Table View Manager
///-----------------------------

@property (weak, readwrite, nonatomic) UITableView *parentTableView;
@property (weak, readwrite, nonatomic) RETableViewManager *tableViewManager;

///-----------------------------
/// @name Managing Cell Height
///-----------------------------

+ (CGFloat)heightWithItem:(RETableViewItem *)item tableViewManager:(RETableViewManager *)tableViewManager;

///-----------------------------
/// @name Working With Keyboard
///-----------------------------

+ (BOOL)canFocusWithItem:(RETableViewItem *)item;

@property (strong, readonly, nonatomic) UIResponder *responder;
@property (strong, readonly, nonatomic) NSIndexPath *indexPathForPreviousResponder;
@property (strong, readonly, nonatomic) NSIndexPath *indexPathForNextResponder;

///-----------------------------
/// @name Managing Cell Appearance
///-----------------------------

@property (strong, readonly, nonatomic) UIImageView *backgroundImageView;
@property (strong, readonly, nonatomic) UIImageView *selectedBackgroundImageView;
@property (strong, readwrite, nonatomic) REActionBar *actionBar;

- (void)updateActionBarNavigationControl;
- (void)layoutDetailView:(UIView *)view minimumWidth:(CGFloat)minimumWidth;

///-----------------------------
/// @name Accessing Row and Section
///-----------------------------

@property (assign, readwrite, nonatomic) NSInteger rowIndex;
@property (assign, readwrite, nonatomic) NSInteger sectionIndex;
@property (weak, readwrite, nonatomic) RETableViewSection *section;
@property (strong, readwrite, nonatomic) RETableViewItem *item;
@property (assign, readonly, nonatomic) RETableViewCellType type;

///-----------------------------
/// @name Handling Cell Events
///-----------------------------

- (void)cellDidLoad;
- (void)cellWillAppear;
- (void)cellDidDisappear;

@property (assign, readonly, nonatomic) BOOL loaded;

@end

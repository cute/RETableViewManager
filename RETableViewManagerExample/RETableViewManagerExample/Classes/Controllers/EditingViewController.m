//
//  EditingViewController.m
//  RETableViewManagerExample
//
//  Created by Roman Efimov on 4/13/13.
//  Copyright (c) 2013 Roman Efimov. All rights reserved.
//

#import "RETableViewCell.h"
#import "EditingViewController.h"

@interface EditingViewController ()<RETableViewCellDelegate,RETableViewManagerDelegate>

@property (strong, readwrite, nonatomic) RETableViewManager *manager;

// Deletable items with confirmation

@property (strong, readwrite, nonatomic) RETableViewItem *itemToDelete;
@property (copy, readwrite, nonatomic) void (^deleteConfirmationHandler)(void);

@end

@implementation EditingViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.navigationItem.rightBarButtonItem = self.editButtonItem;
    self.title = @"Editing";
    
    __typeof (&*self) __weak weakSelf = self;
    
    // Create manager
    //
    self.manager = [[RETableViewManager alloc] initWithTableView:self.tableView delegate:self];
    // Add sections and items
    //
    
    // ================= Deletable =================
    //
    RETableViewSection *section = [RETableViewSection sectionWithHeaderTitle:@"Deletable"];
    [self.manager addSection:section];
    
    for (NSInteger i = 1; i <= 5; i++) {
        RETableViewItem *item = [RETableViewItem itemWithTitle:[NSString stringWithFormat:@"Section 1, Item %li", (long) i] accessoryType:UITableViewCellAccessoryNone selectionHandler:nil];
        item.editingStyle = UITableViewCellEditingStyleDelete;
        item.deletionHandler = ^(RETableViewItem *item) {
            NSLog(@"Item removed: %@", item.title);
        };
        [section addItem:item];
    }
    
    // ================= Deletable with confirmation =================
    //
    section = [RETableViewSection sectionWithHeaderTitle:@"Deletable with confirmation"];
    [self.manager addSection:section];
    
    for (NSInteger i = 1; i <= 5; i++) {
        RETableViewItem *item = [RETableViewItem itemWithTitle:[NSString stringWithFormat:@"Section 2, Item %li", (long) i] accessoryType:UITableViewCellAccessoryNone selectionHandler:nil];
        item.editingStyle = UITableViewCellEditingStyleDelete;
        item.deletionHandlerWithCompletion = ^(RETableViewItem *item, void (^completion)(void)) {
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Confirmation" message:[NSString stringWithFormat:@"Are you sure you want to delete %@", item.title] delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Delete", nil];
            [alert show];
            weakSelf.itemToDelete = item;
            
            // Assign completion block to deleteConfirmationHandler for future use
            //
            weakSelf.deleteConfirmationHandler = completion;
        };
        [section addItem:item];
    }
    
    // ================= Movable =================
    //
    section = [RETableViewSection sectionWithHeaderTitle:@"Movable"];
    [self.manager addSection:section];
    
    for (NSInteger i = 1; i <= 5; i++) {
        RETableViewItem *item = [RETableViewItem itemWithTitle:[NSString stringWithFormat:@"Section 3, Item %li", (long) i] accessoryType:UITableViewCellAccessoryNone selectionHandler:nil];
        item.moveHandler = ^BOOL(id item, NSIndexPath *sourceIndexPath, NSIndexPath *destinationIndexPath) {
            return YES;
        };
        item.moveCompletionHandler = ^(RETableViewItem *item, NSIndexPath *sourceIndexPath, NSIndexPath *destinationIndexPath) {
            NSLog(@"Moved item: %@ from [%li,%li] to [%li,%li]", item.title, (long) sourceIndexPath.section, (long) sourceIndexPath.row, (long) destinationIndexPath.section, (long) destinationIndexPath.row);
        };
        [section addItem:item];
    }
    
    // ================= Deletable & Movable =================
    //
    section = [RETableViewSection sectionWithHeaderTitle:@"Deletable & Movable"];
    [self.manager addSection:section];
    
    for (NSInteger i = 1; i <= 5; i++) {
        RETableViewItem *item = [RETableViewItem itemWithTitle:[NSString stringWithFormat:@"Section 4, Item %li", (long) i] accessoryType:UITableViewCellAccessoryNone selectionHandler:nil];
        item.editingStyle = UITableViewCellEditingStyleDelete;
        item.moveHandler = ^BOOL(id item, NSIndexPath *sourceIndexPath, NSIndexPath *destinationIndexPath) {
            return YES;
        };
        item.moveCompletionHandler = ^(RETableViewItem *item, NSIndexPath *sourceIndexPath, NSIndexPath *destinationIndexPath) {
            NSLog(@"Moved item: %@ from [%li,%li] to [%li,%li]", item.title, (long) sourceIndexPath.section, (long) sourceIndexPath.row, (long) destinationIndexPath.section, (long) destinationIndexPath.row);
        };
        [section addItem:item];
    }
    
    // ================= Can move only within this section =================
    //
    section = [RETableViewSection sectionWithHeaderTitle:@"Can move only within this section"];
    [self.manager addSection:section];
    
    for (NSInteger i = 1; i <= 5; i++) {
        RETableViewItem *item = [RETableViewItem itemWithTitle:[NSString stringWithFormat:@"Section 5, Item %li", (long) i] accessoryType:UITableViewCellAccessoryNone selectionHandler:nil];
        item.moveHandler = ^BOOL(id item, NSIndexPath *sourceIndexPath, NSIndexPath *destinationIndexPath) {
            return (destinationIndexPath.section == section.index);
        };
        [section addItem:item];
    }
    
    // ================= Insert style =================
    //
    section = [[RETableViewSection alloc] initWithHeaderTitle:@"Insert style"];
    [self.manager addSection:section];
    RETableViewItem *item = [RETableViewItem itemWithTitle:[NSString stringWithFormat:@"Section 6, Item %i", 1] accessoryType:UITableViewCellAccessoryNone selectionHandler:nil];
    item.insertionHandler = ^(RETableViewItem *item) {
        NSLog(@"Insertion handler callback");
    };
    item.editingStyle = UITableViewCellEditingStyleInsert;
    [section addItem:item];
}

-(NSArray *) createRightButtons: (int) number
{
    NSMutableArray * result = [NSMutableArray array];
    NSString* titles[2] = {@"Delete", @"More"};
    UIColor * colors[2] = {[UIColor redColor], [UIColor lightGrayColor]};
    for (int i = 0; i < number; ++i)
    {
        MGSwipeButton * button = [MGSwipeButton buttonWithTitle:titles[i] backgroundColor:colors[i] callback:^BOOL(RETableViewCell * sender){
            NSLog(@"Convenience callback received (right).");
            BOOL autoHide = i != 0;
            return autoHide; //Don't autohide in delete button to improve delete expansion animation
        }];
        [result addObject:button];
    }
    return result;
}

- (void)tableView:(UITableView *)tableView willLoadCell:(RETableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath
{
    cell.textLabel.font = [UIFont systemFontOfSize:16];
    cell.delegate = self;
    cell.allowsMultipleSwipe = NO;
    cell.rightSwipeSettings.transition = MGSwipeTransitionBorder;
    cell.rightExpansion.fillOnTrigger = YES;
}

-(NSArray*) swipeTableCell:(RETableViewCell*) cell swipeButtonsForDirection:(MGSwipeDirection)direction
             swipeSettings:(MGSwipeSettings*) swipeSettings expansionSettings:(MGSwipeExpansionSettings*) expansionSettings;
{
    if (direction == MGSwipeDirectionRightToLeft) {
        expansionSettings.fillOnTrigger = NO;
        return [self createRightButtons:2];
    }
    return nil;
}

-(BOOL) swipeTableCell:(RETableViewCell*) cell tappedButtonAtIndex:(NSInteger) index direction:(MGSwipeDirection)direction fromExpansion:(BOOL) fromExpansion
{
    NSLog(@"Delegate: button tapped, %@ position, index %d, from Expansion: %@",
          direction == MGSwipeDirectionLeftToRight ? @"left" : @"right", (int)index, fromExpansion ? @"YES" : @"NO");
    
    if (direction == MGSwipeDirectionRightToLeft && index == 0) {
        //delete button
        NSIndexPath * path = [self.tableView indexPathForCell:cell];
        [self.tableView deleteRowsAtIndexPaths:@[path] withRowAnimation:UITableViewRowAnimationLeft];
        return NO; //Don't autohide to improve delete expansion animation
    }
    
    return YES;
}

-(void) tableView:(UITableView *)tableView accessoryButtonTappedForRowWithIndexPath:(NSIndexPath *)indexPath
{
    NSLog(@"Tapped accessory button");
}

#pragma mark -
#pragma mark UIAlertViewDeletate

- (void)alertView:(UIAlertView *)alertView willDismissWithButtonIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 1) {
        if (self.deleteConfirmationHandler) {
            self.deleteConfirmationHandler();
            NSLog(@"Item removed: %@", self.itemToDelete.title);
        }
    }
}

@end
